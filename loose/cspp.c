// iterative
// constrained shortest path problem
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define byte unsigned char

struct connection {
  int to, from;
  int time, cost;
};

struct State {
    int island;
    int time;
    int cost;
};

struct PriorityQueue {
    struct State *heap;
    int capacity;       // How big the allocated array is
    int size;           // How many items are currently in the heap
};

void swapState(struct State *a, struct State *b) {
    struct State temp = *a;
    *a = *b;
    *b = temp;
}

// start pq
// the heap works as a tree thing because that way we can sort things in log n time not n time
struct PriorityQueue* createPQ() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->heap = (struct State*)malloc(10 * sizeof(struct State));
    pq->capacity = 10;
    pq->size = 0;
    return pq;
}

// push
void heapifyUp(struct PriorityQueue* pq, int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && pq->heap[index].time < pq->heap[parent].time) {
        swapState(&pq->heap[index], &pq->heap[parent]);
        heapifyUp(pq, parent);
    }
}

void push(struct PriorityQueue* pq, struct State newState) {
    if (pq->size == pq->capacity) {
      int capacity = pq->capacity*2;
      struct State *newAdress = realloc(pq->heap, capacity * sizeof(struct State));
      if (newAdress == NULL) return;
      pq->heap = newAdress;
      pq->capacity = capacity;

    }     
    pq->heap[pq->size] = newState;
    pq->size++;
    heapifyUp(pq, pq->size - 1);
}

// pop
void heapifyDown(struct PriorityQueue* pq, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < pq->size && pq->heap[left].time < pq->heap[smallest].time) {
        smallest = left;
    }
    if (right < pq->size && pq->heap[right].time < pq->heap[smallest].time) {
        smallest = right;
    }

    if (smallest != index) {
        swapState(&pq->heap[index], &pq->heap[smallest]);
        heapifyDown(pq, smallest);
    }
}

struct State pop(struct PriorityQueue* pq) {
    struct State root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return root;
}

void cspp (int startNode, int budget, int **nodes, struct connection *connections, int connectionsNum) {
  struct PriorityQueue *pq = createPQ();
  
  struct State initialState = {startNode, 0, 0};
  push(pq, initialState);

  while (pq->size > 0) {
    struct State currentState = pop(pq);
    if (currentState.time > nodes[currentState.island-1][currentState.cost]) continue;
    for (int i = 0; i < connectionsNum; i++) {
      int island = -1;
      if (connections[i].to == currentState.island) {
        island = connections[i].from;
      }
      if (connections[i].from == currentState.island) {
        island = connections[i].to;
      }
      if (island != -1) {
        if (currentState.cost + connections[i].cost <= budget && currentState.time + connections[i].time < nodes[island-1][currentState.cost + connections[i].cost]) {
          nodes[island-1][currentState.cost + connections[i].cost] = currentState.time + connections[i].time;
          struct State nextState = {island, currentState.time + connections[i].time, currentState.cost + connections[i].cost};
          push(pq, nextState);
        }
      }
    }
  }
  free(pq -> heap);
  free(pq);
  return;
}

int main () {
  int budget; // money constraint, can be interpret as some other shit thought and thus aplied to other things
  int nodesNum;
  int connectionsNum;
  scanf("%d", &budget);
  scanf("%d", &nodesNum);
  scanf("%d", &connectionsNum);
  int **nodes = malloc(nodesNum * sizeof(int *));
  for (int i = 0; i < nodesNum; i++) {
    nodes[i] = malloc((budget+1)*sizeof(int));
    for (int i2 = 0; i2 < budget+1; i2++) {
      nodes[i][i2] = INT_MAX;
    }
  }
  struct connection *connections = malloc(connectionsNum * sizeof(struct connection));
  for (int i = 0; i < connectionsNum; i++) {
    scanf("%d", &connections[i].to);
    scanf("%d", &connections[i].from);
    scanf("%d", &connections[i].time);
    scanf("%d", &connections[i].cost);
  }
  // fixed cuz wathever
  int from, to;
  scanf("%d", &from);
  scanf("%d", &to);
  nodes[from-1][0] = 0;
  cspp(from, budget, nodes, connections, connectionsNum);
  int answer = INT_MAX;
  for (int i = 0; i <= budget; i++) {
    if (nodes[to - 1][i] < answer) {
      answer = nodes[to - 1][i];
    }
  }
  if (answer == INT_MAX) printf("-1\n");
  else printf("%d\n", answer);
  for (int i = 0; i < nodesNum; i++) {
      free(nodes[i]);
  }
  free(nodes);
  free(connections);
  return 0;
}
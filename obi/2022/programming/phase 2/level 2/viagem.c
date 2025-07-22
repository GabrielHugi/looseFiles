#include <stdio.h>
#include <stdlib.h>
#define byte unsigned char


struct connection {
  int to, from;
  int time, cost;
};

void find(int currentIsland, int currentTime, int currentCost, int budget, int **islandTimes, struct connection *connections, int connectionNum, int islandNum) {
  if (currentTime > islandTimes[currentIsland-1][currentCost]) {
    return;
  }

  for (int i = 0; i < connectionNum; i++) {
    if (connections[i].from == currentIsland) {
      if (connections[i].cost + currentCost <= budget && currentTime + connections[i].time < islandTimes[connections[i].to-1][connections[i].cost + currentCost]) {        
        islandTimes[connections[i].to-1][connections[i].cost + currentCost] = currentTime + connections[i].time;  
        find(connections[i].to, currentTime + connections[i].time, connections[i].cost + currentCost, budget, islandTimes, connections, connectionNum, islandNum);
      }
    }
    if (connections[i].to == currentIsland) {
      if (connections[i].cost + currentCost <= budget && currentTime + connections[i].time < islandTimes[connections[i].from-1][connections[i].cost + currentCost]) {        
        islandTimes[connections[i].from-1][connections[i].cost + currentCost] = currentTime + connections[i].time;  
        find(connections[i].from, currentTime + connections[i].time, connections[i].cost + currentCost, budget, islandTimes, connections, connectionNum, islandNum);
      }
    }
  }
  return;
}

int main () {
  int budget;
  int islandNum;
  int connectionNum;
  scanf("%d", &budget);
  scanf("%d", &islandNum);
  scanf("%d", &connectionNum);
  struct connection *connections = malloc(connectionNum * sizeof(struct connection));;
  for (int i = 0; i < connectionNum; i++) {
    int to, from, time, cost;
    scanf("%d", &to);
    scanf("%d", &from);
    scanf("%d", &time);
    scanf("%d", &cost);
    connections[i].to = to;
    connections[i].from = from;
    connections[i].time = time;
    connections[i].cost = cost;
  }
  int to, from;
  scanf("%d", &from);
  scanf("%d", &to);
  // this way i can track the times for every possible price to get in this bs
  int **islandTimes = malloc(islandNum * sizeof(int *));
    for (int i = 0; i < islandNum; i++) {
        islandTimes[i] = malloc((budget + 1) * sizeof(int));
        for (int j = 0; j <= budget; j++) {
            islandTimes[i][j] = __INT_MAX__;
        }
    }
  islandTimes[from-1][0] = 0;
  find(from, 0, 0, budget, islandTimes, connections, connectionNum, islandNum);
  int answer = __INT_MAX__;
  for (int i = 0; i <= budget; i++) {
    if (islandTimes[to - 1][i] < answer) {
      answer = islandTimes[to - 1][i];
    }
  }
  if (answer == __INT_MAX__) printf("-1\n");
  else printf("%d\n", answer);
  for (int i = 0; i < islandNum; i++) {
      free(islandTimes[i]);
  }
  free(islandTimes);
  free(connections);
  return 0;
}
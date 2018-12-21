#include "election.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  state_t result;
  const char * ptr = line;
  int label[2] = {0};
  int label_ind = 0;
  int ptr_ind = 0;
  while (*(ptr + ptr_ind)) {
    if (*(ptr + ptr_ind) == ':') {
      label[label_ind] = ptr_ind;
      label_ind++;
    }
    ptr_ind++;
  }
  if (label[0] > 63) {
    printf("Aha,state name is toooo long!!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < label[0]; i++) {
    result.name[i] = *(ptr + i);
  }
  result.name[label[0]] = '\0';
  result.population = atoi(ptr + label[0] + 1);
  result.electoralVotes = atoi(ptr + label[1] + 1);
  return result;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  unsigned int total_vote = 0;
  size_t index = 0;
  while (index < nStates) {
    double percent = (double)*(voteCounts + index) / (double)(stateData + index)->population;
    if (percent > 0.5) {
      total_vote += (stateData + index)->electoralVotes;
    }
    index++;
  }
  return total_vote;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  size_t index = 0;
  while (index < nStates) {
    double percent = (double)*(voteCounts + index) / (double)(stateData + index)->population;
    if (percent >= 0.495 && percent <= 0.505) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             (stateData + index)->name,
             percent * 100);
    }
    index++;
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  size_t index = 0;
  double max_per = 0.0;
  size_t label_ind = 0;
  while (index < nStates) {
    double percent = (double)*(voteCounts + index) / (double)(stateData + index)->population;
    if (percent > max_per) {
      max_per = percent;
      label_ind = index;
    }
    index++;
  }
  printf(
      "Candidate A won %s with %.2f%% of the vote\n", (stateData + label_ind)->name, max_per * 100);
}

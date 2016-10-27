#include <stdio.h>
#include <stdbool.h>

#define EVENTLOG_SIZE 10

struct EventLogEntry {
  unsigned char type;
  unsigned long time;
};

class EventLog {
  EventLogEntry eventLog[EVENTLOG_SIZE];
  unsigned char last = 0;
  unsigned char size = 0;
  unsigned char sentId = 0;
  unsigned char savedId = 0;

public:
  void addEvent(unsigned char type, unsigned long time) {
    eventLog[last].type = type;
    eventLog[last].time = time;
    last++;
    if (last >= EVENTLOG_SIZE) {
      last = 0;
    }
    size++;
    if (size > EVENTLOG_SIZE) {
      size = EVENTLOG_SIZE;
    }
  }

  EventLogEntry getEvent(unsigned char index) {
    return eventLog[index];
  }

  unsigned char getLast() {
    return last;
  }

  unsigned int getSize() {
    return size;
  }

};

EventLog e;

int main(void) {
        int i;
        for (i = 0; i < EVENTLOG_SIZE+3 ; i++) {
                e.addEvent(i, i*1000);
        }

        printf("Event log: ");
        for (i = 0; i < EVENTLOG_SIZE ; i++) {
                EventLogEntry ee=e.getEvent(i);
                printf("%u, ", ee.type);
        }

        printf("\nSize: %u Last: %u\n", e.getSize(), e.getLast());

        int k = 0;
        int n = e.getSize();
        for (i = e.getLast(); k < n; i = (i+1)%EVENTLOG_SIZE) {
                printf("Log entry: %d [%u]\n", k, e.getEvent(i).type);
                k++;
        }
        return 0;
}

#include <stdio.h>
#include <stdbool.h>

#include <iostream>
#include <sys/time.h>

#define EVENTLOG_SIZE 10

struct EventLogEntry {
  unsigned char type;
  unsigned long time;
};

class EventLog {
  EventLogEntry eventLog[EVENTLOG_SIZE];
  unsigned char last = 0;
  unsigned int size = 0;
  unsigned long sentTime = 0;
  unsigned long savedTime = 0;

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

  unsigned int getNextTimestampId(unsigned long timeStamp) {
	unsigned int timeStampId;
	bool halfSearch = false;
	for (int i = 0; i < EVENTLOG_SIZE; i++) {
		if (eventLog[i].time <= timeStamp && !halfSearch) {
			halfSearch = true;
		}
		if (halfSearch && eventLog[i].time >= timeStamp) {
			timeStampId = i;
			break;
		}
	}
	return timeStampId;
  }

};

EventLog e;

	void printLastEvents(unsigned long timeStampAfter) {
		printf("\nPrinting all log entries after %lu:\n", timeStampAfter);
		int k = 0;
		int n = e.getSize();
		for (unsigned long i = e.getNextTimestampId(timeStampAfter); k < n; i = (i+1)%EVENTLOG_SIZE) {
			if (e.getEvent(i).time < timeStampAfter) {
				break;
			}
			printf("Log entry: %d:%lu [%lu] %u \n", k, i, e.getEvent(i).time,  e.getEvent(i).type);
			k++;
		}
		
	}

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
		printf("Log entry: %d [%lu] %u\n", k, e.getEvent(i).time, e.getEvent(i).type);
		k++;
	}
	
	printLastEvents(5000);

	return 0;
}


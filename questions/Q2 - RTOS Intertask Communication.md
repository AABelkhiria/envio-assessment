# RTOS Interstak Communication

*ADD CONTENTS HERE*

### Questions
---
You are writing a firmware application for MCU (any `ARM Cortex MCU`). Your application needs to poll data from a sensor and do some processing with the data. Your application is based on `RTOS` (e.g. freeRTOS) and have 2 tasks (threads): 

- POLLING task

- PROCESSING task

**POLLING** task is regularly polling data from a sensor, and stores information locally, while the **PROCESSING** task needs to take that data and process it. Two tasks are operating with different speed and they need to be synchronized. 

```
- How would you implement the intertask communication model? 
```
```
- What other task synchronization techniques do you know?
```

### Answers
---

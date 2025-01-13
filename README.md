# TkClock

CLI task manager

---

## Getting Started
To get a local copy up and running, follow these steps:

### Installation

1. **Clone the repo**
   ```bash
   git clone https://github.com/erlonr/tkclock.git
   ```

## Usage
1. Create a tasks.txt file.
2. Open the tasks.txt file and enter the tasks separating the values with a comma.
    ```
    0,time_in_minutes,task 1
    0,time_in_minutes,task 2
    0,time_in_minutes,task 3
    ...
    0,time_in_minutes,task N
    ```
3. Run the program in the same directory as the tasks.txt file, passing the task name as an argument. if the task name has more than one word, use quotation marks.
    - Linux:
        ```bash
        ./path_to/bin/tkclock "task name"
        ```
4. To print all tasks and check which ones have been completed, run the program in the same directory as the tasks.txt file, without passing any arguments.
    - Linux
        ```bash
        ./path_to/bin/tkclock
        ```

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Contact
Project Link: [https://github.com/erlonr/tkclock](https://github.com/erlonr/tkclock)
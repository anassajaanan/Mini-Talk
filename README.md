# **MiniTalk Project**

## **Description**

MiniTalk is a client-server communication program developed for 42 curriculum. The project focuses on inter-process communication using UNIX signals **`SIGUSR1`** and **`SIGUSR2`**. The server and client applications exchange messages, allowing the server to receive and display the transmitted messages from clients.

## **Server Implementation**

The server implementation can be found in the **`server.c`** file. It starts by displaying its own PID and sets up the signal handlers using **`sigaction`**. The server maintains a global state using the **`t_global_state`** structure defined in **`minitalk.h`**, which consists of **`data_byte`** and **`bits_count`**. The server uses these variables to reconstruct the received message and prints it when a byte is completed.

## **Client Implementation**

The client implementation resides in the **`client.c`** file. It takes two parameters: the server PID and the message to be sent. The client also uses **`sigaction`** to set up signal handlers for acknowledgment messages from the server. The **`send_character_signal`** function sends the individual characters of the message to the server, and **`send_message_to_server`** sends the entire message, including the newline and acknowledgment signals.

## **Bitwise Operations for Data Transmission**

In MiniTalk, data transmission between the client and server is achieved using bitwise operations. The **`send_character_signal`** function in the client.c file is responsible for sending individual characters of the message to the server using bitwise operations. Here's an explanation of how it works:

1. The function **`send_character_signal`** takes the server PID and a character (data) as parameters.
2. For each character (data), the function sends the individual bits to the server using signals. It sends one bit at a time, from the least significant bit (LSB) to the most significant bit (MSB).
3. The function iterates 8 times (for each bit of the character) using a loop with a variable **`i`**.
4. Inside the loop, the function masks the current bit of the character using bitwise left shift operator **`<<`** combined with the bitwise AND operator **`&`**.
5. If the bit is 0, the function sends a **`SIGUSR2`** signal to the server. Otherwise, it sends a **`SIGUSR1`** signal.
6. After sending the signal, the function waits for a short duration using **`usleep`** to ensure that the server has enough time to handle the signal before sending the next one.
7. Once all 8 bits of the character are sent, the loop is completed, and the function proceeds to the next character in the message.
8. The function also sends a **`SIGUSR2`** signal after sending the last character of the message to indicate the end of the message.

By using bitwise operations, the client can send each character efficiently by breaking it down into individual bits and sending them sequentially through signals. Similarly, the server uses bitwise operations to reconstruct the original character and display the received message.

## **Makefile**

The project includes a **`Makefile`** to compile the source files without relinking. The Makefile supports the following commands:

- **`all`**: Compiles both the server and client executables.
- **`server`**: Compiles only the server executable.
- **`client`**: Compiles only the client executable.
- **`bonus`**: Compiles both executables, including bonus features (if implemented).
- **`clean`**: Removes object files.
- **`fclean`**: Removes object files and executables.
- **`re`**: Cleans, then recompiles the project.

## **Bonus Features**

The project offers the opportunity to implement bonus features if the mandatory part is completed flawlessly. The bonus features include:

1. **Server Acknowledgment**: The server acknowledges every received message by sending back a signal to the client.
2. **Unicode Characters Support**: Extending the communication to support Unicode characters.

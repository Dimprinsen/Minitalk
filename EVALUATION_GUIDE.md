# Minitalk - Evaluation Preparation Guide

## Pre-Evaluation Checklist

### 1. Compilation & Clean Build
```bash
# Clean everything
make fclean

# Rebuild from scratch
make

# Verify executables created
ls -l server client

# Test that make doesn't relink unnecessarily
make
# Should output: "make: Nothing to be done for 'all'."
```

### 2. Norm Check
```bash
# Check all .c and .h files for norm compliance
norminette *.c
norminette ft_printf/*.c ft_printf/*.h
```

### 3. Memory Leak Check (Optional - but impressive to show)
```bash
# Terminal 1: Run server with valgrind
valgrind --leak-check=full ./server

# Terminal 2: Send a message
./client <PID> "Test message"

# Then Ctrl+C the server and check valgrind output
# Should show: "All heap blocks were freed -- no leaks are possible"
```

---

## During Evaluation

### Step 1: Compile the Project
```bash
make
```
**Expected output:**
- Should compile without errors or warnings
- Creates `server` and `client` executables

### Step 2: Demonstrate Basic Functionality

#### Terminal 1 (Server):
```bash
./server
```
**Expected output:**
```
Server PID: <some_number>
```
**Note the PID!** You'll need it for the client.

#### Terminal 2 (Client):
```bash
# Replace <PID> with the actual server PID
./client <PID> "Hello World!"
```

**Expected behavior:**
- Terminal 1 (server) displays: `Hello World!`
- Terminal 2 (client) displays: `Signal received!`

### Step 3: Test Different Messages

```bash
# Short message
./client <PID> "Hi"

# Long message
./client <PID> "This is a longer message to demonstrate that the communication works properly even with extended strings."

# Message with special characters
./client <PID> "Test! @#$% 123 & more..."

# Empty message (edge case)
./client <PID> ""

# Message with spaces
./client <PID> "Multiple    spaces    test"
```

### Step 4: Test Unicode Support (Bonus)
```bash
# Emojis
./client <PID> "😀🎉🚀"

# Chinese characters
./client <PID> "你好世界"

# Mixed Unicode
./client <PID> "Hello 世界 🌍!"
```

### Step 5: Test Multiple Sequential Messages
```bash
# Send multiple messages one after another
./client <PID> "Message 1"
./client <PID> "Message 2"
./client <PID> "Message 3"
```
**Expected:** Server should handle all without needing restart.

### Step 6: Test Error Handling

```bash
# Invalid PID
./client 123 "test"
# Expected: "Invalid server PID: 123"

# Wrong number of arguments
./client
# Expected: "Usage: ./client <server_pid> <message>"

./client 12345
# Expected: "Usage: ./client <server_pid> <message>"

# Non-existent PID
./client 99999 "test"
# Expected: "Failed to send signal to PID 99999"
```

---

## Questions You Might Be Asked

### 1. "How does your program work?"
**Answer:**
- Server starts and prints its PID, then waits for signals
- Client converts each character of the message into bits (8 bits per byte)
- For each bit: sends SIGUSR1 if bit is 1, SIGUSR2 if bit is 0
- Server receives signals and reconstructs the bits into characters
- Server sends acknowledgment (SIGUSR1) after each byte
- When null terminator is received, server sends SIGUSR2 to indicate completion

### 2. "Why do you use SIGUSR1 and SIGUSR2?"
**Answer:**
These are user-defined signals in UNIX specifically for custom inter-process communication. They're perfect for this project because we can define their meaning: SIGUSR1 = bit 1, SIGUSR2 = bit 0.

### 3. "What is the global variable and why is it allowed?"
**Answer:**
- Client: `g_ack_received` - volatile sig_atomic_t flag
- Used for signal-safe communication between signal handler and main program
- Volatile ensures the compiler doesn't optimize away reads/writes
- sig_atomic_t ensures atomic read/write operations (no race conditions)
- Necessary because signal handlers run asynchronously

### 4. "How do you handle Unicode?"
**Answer:**
UTF-8 encoding represents characters as 1-4 bytes. Since we transmit byte-by-byte (8 bits at a time), multi-byte UTF-8 sequences are automatically preserved and work correctly.

### 5. "What happens if signals are sent too fast?"
**Answer:**
Linux doesn't queue SIGUSR signals - if multiple arrive while one is pending, some are lost. To handle this:
- We use `usleep(300)` to pace signal transmission
- Server sends acknowledgment after each byte
- Client waits for acknowledgment before sending next byte

### 6. "Why use sigaction instead of signal?"
**Answer:**
`sigaction()` provides:
- More control with flags (SA_SIGINFO)
- Access to sender's PID via siginfo_t
- More portable and reliable behavior across systems
- Avoids the undefined behavior of older signal() implementations

### 7. "Can you explain the bit manipulation?"
**Answer:**
- `(str[i] >> bit) & 1` - shifts right to get specific bit, masks with 1
- `current |= (0x01 << i)` - sets the i-th bit in current byte
- We send LSB (Least Significant Bit) first, building up each byte

---

## Common Pitfalls to Avoid

1. **Don't run client and server in the same terminal** - Open two separate terminals
2. **Use the correct PID** - Copy it carefully from the server output
3. **Don't Ctrl+C the server** while client is sending - let messages complete
4. **Quote the message** if it contains spaces or special characters

---

## Code Walkthrough Points

### Server (server.c)
- `bit_handler()`: Signal handler that reconstructs bytes from bits
- Static variables maintain state between signal calls
- Sends acknowledgment after each complete byte
- Prints character when byte is complete

### Client (client.c)
- `send_message()`: Converts each byte to 8 bits and sends as signals
- Waits for acknowledgment after each byte
- Uses global flag for signal-safe synchronization
- Error handling for failed signal sends

### Makefile
- Proper dependencies to avoid unnecessary relinking
- Uses ft_printf library (your own implementation)
- Clean, fclean, and re rules work correctly
- Bonus rule ready (even if bonus files don't exist yet)

---

## Final Tips

1. **Be confident** - Your code works and handles the requirements
2. **Explain clearly** - Show you understand signals and bit manipulation
3. **Demo Unicode** - It's a bonus feature and impressive
4. **Show error handling** - Demonstrates thoroughness
5. **Run norminette** - Prove your code follows the Norm
6. **Keep terminals organized** - Label which is server/client

Good luck with your evaluation! 🚀

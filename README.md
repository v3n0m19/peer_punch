Hole chat is a chat application based on the concept of UDP hole punching. It is cli based and work only with linux to limitations of thread creation and other stuff in windows. 

To use the application:

1. Clone the repository:

    ```$ git clone https://github.com/v3n0m19/peer_punch.git``` 

2. Navigate to the project directory

    ```$ cd peer_punch```

3. Compile the application using make

    ```$ make```

4. Run the application

    ```$ ./peerpunch```

## License

This project is licensed under the MIT License. Please refer to the LICENSE file for more details.

## Contributing

Currently the application has some issues(which I am aware of)like:
1. There is no scroll feature
2. There are some losses and out of order message delivery (This is an inherent problem UDP :( )
3. The messages aren't encrypted
4. The indentation of terminal changes after running the application (which is currently fixed by running the reset command everytime someone runs  make)

I won't be working on this anymore but I am thinking of rewriting it in python along with (hopefully) integrating TCP hole punching as well.

Anyone is free to contribute and fix the above stated issues and anyother issues that they find
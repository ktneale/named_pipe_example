# named_pipe_example

Two processes communicating via a named pipe.

### To compile

```gcc server.c -o server```


```gcc client.c -o client```


### To run

Start the server first:

``` ./server ```

Then the client:

``` ./client ```



These two processes should recover from disconnection events.

Based on: https://brandonwamboldt.ca/how-linux-pipes-work-under-the-hood-1518/

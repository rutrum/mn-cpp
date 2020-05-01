test TEST:
    g++ {{ TEST }} -o bin/test
    bin/test
    @echo "Success!"
    

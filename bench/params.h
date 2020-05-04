int start = 0;
int end = 1000;
switch (argc) {
    case 3:
        start = strtol(argv[1], NULL, 12);
        end = strtol(argv[2], NULL, 12);
        break;
    case 2:
        end = strtol(argv[1], NULL, 12);
}

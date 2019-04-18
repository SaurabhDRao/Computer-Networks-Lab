BEGIN {
    tcp = 0;
    udp = 0;
} {
    event = $1;
    type = $5;
    if((type == "cbr") && ((event == "r") || (event == "d")))
        udp++;
    if((type == "tcp") && ((event == "r") || (event == "d")))
        tcp++;
} END {
    printf("Number of TCP packets: %d\n", tcp);
    printf("Number of UDP packets: %d\n", udp);
}
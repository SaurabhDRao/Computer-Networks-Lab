set ns [new Simulator]
set nf [open out.nam w]
set tr [open out.tr w]
$ns namtrace-all $nf
$ns trace-all $tr

proc finish {} {
    global ns nf tr
    $ns flush-trace
    close $nf
    close $tr
    exec nam out.nam &
    exit 0
}

$ns color 1 Red
$ns color 2 Blue

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$n0 color Red
$n1 color Blue
$n3 color Purple

$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail

$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right

set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp1

set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1

$ns connect $tcp1 $sink1

set ftp [new Application/FTP]
$ftp attach-agent $tcp1

$tcp1 set fid_ 1

Agent/TCP set packetsize_ 1000

set tcp2 [new Agent/TCP]
$ns attach-agent $n1 $tcp2

set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2

$ns connect $tcp2 $sink2

set telnet [new Application/Telnet]
$telnet set interval_ 0.005
$telnet attach-agent $tcp2

$tcp2 set fid_ 2

$ns at 0.5 "$telnet start"
$ns at 4.5 "$telnet stop"
$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 5.0 "finish"

$ns run
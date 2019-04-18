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
    exec awk -f cwnd.awk cwnd1.tr > tcp1.tr
    exec awk -f cwnd.awk cwnd2.tr > tcp2.tr
    exit 0
}

$ns color 1 Red
$ns color 2 Blue

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]

$n0 color Red
$n6 color Orange
$n7 color Blue
$n5 color Green

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n7 $n2 1Mb 10ms DropTail

$ns make-lan "$n1 $n2 $n3 $n4 $n5 $n6" 2Mb 40ms LL Queue/DropTail Mac/802_3

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n7 $n2 orient right

$ns queue-limit $n0 $n1 20
$ns queue-limit $n7 $n2 20

set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp1

set sink1 [new Agent/TCPSink]
$ns attach-agent $n6 $sink1

$ns connect $tcp1 $sink1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1

$tcp1 set fid_ 1
$tcp1 set packetsize_ 55

set tfile1 [open cwnd1.tr w]
$tcp1 attach $tfile1
$tcp1 trace cwnd_

set tcp2 [new Agent/TCP]
$ns attach-agent $n7 $tcp2

set sink2 [new Agent/TCPSink]
$ns attach-agent $n5 $sink2

$ns connect $tcp2 $sink2

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2

$tcp2 set fid_ 2
$tcp1 set packetsize_ 55

set tfile2 [open cwnd2.tr w]
$tcp2 attach $tfile2
$tcp2 trace cwnd_

$ns at 0.5 "$ftp1 start"
$ns at 4.5 "$ftp1 stop"
$ns at 1.0 "$ftp2 start"
$ns at 4.0 "$ftp2 stop"
$ns at 5.0 "finish"

$ns run
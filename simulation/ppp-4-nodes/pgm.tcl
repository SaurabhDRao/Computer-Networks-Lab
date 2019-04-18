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

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink

$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp

$tcp set fid_ 1

set udp [new Agent/UDP]
$ns attach-agent $n1 $udp

set null [new Agent/Null]
$ns attach-agent $n3 $null

$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr set packetsize_ 500
$cbr set interval_ 0.005
$cbr attach-agent $udp

$udp set fid_ 2

$ns at 0.5 "$cbr start"
$ns at 4.5 "$cbr stop"
$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 5.0 "finish"

$ns run
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

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.25Mb 15ms DropTail

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

$ns queue-limit $n0 $n1 10
$ns queue-limit $n1 $n2 15

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp

set null [new Agent/Null]
$ns attach-agent $n2 $null

$ns connect $udp $null

set cbr [new Application/Traffic/CBR]
$cbr set packetsize_ 500
$cbr set interval_ 0.005

$cbr attach-agent $udp

$ns at 0.5 "$cbr start"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"

$ns run
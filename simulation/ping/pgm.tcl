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
set n4 [$ns node]
set n5 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n0 $n3 1Mb 10ms DropTail
$ns duplex-link $n0 $n4 1Mb 10ms DropTail
$ns duplex-link $n0 $n5 1Mb 10ms DropTail

Agent/Ping instproc recv { from rtt } {
    $self instvar node_
    puts "node [$node_ id] received ping answer from $from with round trip time $rtt ms"
}

$ns queue-limit $n0 $n2 0

set p1 [new Agent/Ping]
$ns attach-agent $n1 $p1

set p2 [new Agent/Ping]
$ns attach-agent $n2 $p2

set p3 [new Agent/Ping]
$ns attach-agent $n3 $p3

set p4 [new Agent/Ping]
$ns attach-agent $n4 $p4

$ns connect $p1 $p2
$ns connect $p3 $p4

$ns at 0.1 "$p1 send"
$ns at 0.3 "$p2 send"
$ns at 0.5 "$p3 send"
$ns at 0.7 "$p4 send"
$ns at 0.9 "$p3 send"
$ns at 1.0 "finish"

$ns run
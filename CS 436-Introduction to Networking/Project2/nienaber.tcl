set ns [new Simulator]

set rtproto DV

set tracefd [open nienaber.tr w]
$ns trace-all $tracefd

#Creates 18 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]
set n10 [$ns node]
set n11 [$ns node]
set n12 [$ns node]
set n13 [$ns node]
set n14 [$ns node]
set n15 [$ns node]
set n16 [$ns node]
set n17 [$ns node]


#Creates duplex links
$ns duplex-link $n8 $n0 1Mb 20ms DropTail
$ns duplex-link $n9 $n1 1Mb 20ms DropTail
$ns duplex-link $n0 $n2 2Mb 40ms DropTail
$ns duplex-link $n1 $n2 2Mb 40ms DropTail
$ns duplex-link $n2 $n3 8Mb 100ms DropTail
$ns duplex-link $n2 $n4 8Mb 100ms DropTail
$ns duplex-link $n3 $n4 8Mb 100ms DropTail
$ns duplex-link $n3 $n5 2Mb 40ms DropTail
$ns duplex-link $n4 $n6 2Mb 40ms DropTail
$ns duplex-link $n4 $n7 2Mb 40ms DropTail
$ns duplex-link $n5 $n10 1Mb 20ms DropTail
$ns duplex-link $n5 $n11 1Mb 20ms DropTail
$ns duplex-link $n5 $n12 1Mb 20ms DropTail
$ns duplex-link $n5 $n13 1Mb 20ms DropTail
$ns duplex-link $n6 $n14 1Mb 20ms DropTail
$ns duplex-link $n6 $n15 1Mb 20ms DropTail
$ns duplex-link $n7 $n16 1Mb 20ms DropTail
$ns duplex-link $n7 $n17 1Mb 20ms DropTail

#Sets Queue Limits
$ns queue-limit $n8 $n0 20
$ns queue-limit $n9 $n1 20
$ns queue-limit $n0 $n2 25
$ns queue-limit $n1 $n2 25
$ns queue-limit $n2 $n3 30
$ns queue-limit $n2 $n4 30
$ns queue-limit $n3 $n4 30
$ns queue-limit $n3 $n5 25
$ns queue-limit $n4 $n6 25
$ns queue-limit $n4 $n7 25
$ns queue-limit $n5 $n10 20
$ns queue-limit $n5 $n11 20
$ns queue-limit $n5 $n12 20
$ns queue-limit $n5 $n13 20
$ns queue-limit $n6 $n14 20
$ns queue-limit $n6 $n15 20
$ns queue-limit $n7 $n16 20
$ns queue-limit $n7 $n17 20

#Creates 4 UDP Agents and attachs them to node 9
set udp0 [new Agent/UDP]
set udp1 [new Agent/UDP]
set udp2 [new Agent/UDP]
set udp3 [new Agent/UDP]
$ns attach-agent $n9 $udp0
$ns attach-agent $n9 $udp1
$ns attach-agent $n9 $udp2
$ns attach-agent $n9 $udp3

#CBR Agent for n9-n12
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 1000
$cbr0 set interval_ 0.005
$cbr0 set random_ 1
$cbr0 attach-agent $udp0

#CBR Agent for n9-n13
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 3000
$cbr1 set interval_ 0.005
$cbr1 set random_ 1
$cbr1 attach-agent $udp1

#CBR Agent for n9-n15
set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 2000
$cbr2 set interval_ 0.005
$cbr2 set random_ 1
$cbr2 attach-agent $udp2

#CBR Agent for n9-n17
set cbr3 [new Application/Traffic/CBR]
$cbr3 set packetSize_ 2000
$cbr3 set interval_ 0.005
$cbr3 set random_ 1
$cbr3 attach-agent $udp3

#Creates 4 TCP Agents and attachs them to node 8
set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
set tcp2 [new Agent/TCP]
set tcp3 [new Agent/TCP]
$ns attach-agent $n8 $tcp0
$ns attach-agent $n8 $tcp1
$ns attach-agent $n8 $tcp2
$ns attach-agent $n8 $tcp3

#CBR Agent for n8-n10
set cbr4 [new Application/Traffic/CBR]
$cbr4 set packetSize_ 1000
$cbr4 set interval_ 0.005
$cbr4 set random_ 1
$cbr4 attach-agent $tcp0

#CBR Agent for n8-n11
set cbr5 [new Application/Traffic/CBR]
$cbr5 set packetSize_ 3000
$cbr5 set interval_ 0.005
$cbr5 set random_ 1
$cbr5 attach-agent $tcp1

#CBR Agent for n8-n14
set cbr6 [new Application/Traffic/CBR]
$cbr6 set packetSize_ 2000
$cbr6 set interval_ 0.005
$cbr6 set random_ 1
$cbr6 attach-agent $tcp2

#CBR Agent for n8-n16
set cbr7 [new Application/Traffic/CBR]
$cbr7 set packetSize_ 2000
$cbr7 set interval_ 0.005
$cbr7 set random_ 1
$cbr7 attach-agent $tcp3

#Sets flow id for n8-n10, n9-n12, n8-n14, and n9-n15
$tcp0 set fid_ 0
$udp0 set fid_ 1
$tcp2 set fid_ 2
$udp2 set fid_ 3

#Creates a LossMonitor agent for n12, n13, n15,and n17
set sink0 [new Agent/LossMonitor]
set sink1 [new Agent/LossMonitor]
set sink2 [new Agent/LossMonitor]
set sink3 [new Agent/LossMonitor]
$ns attach-agent $n12 $sink0
$ns attach-agent $n13 $sink1
$ns attach-agent $n15 $sink2
$ns attach-agent $n17 $sink3

#Connects UDP sources to LossMonitors
$ns connect $udp0 $sink0
$ns connect $udp1 $sink1
$ns connect $udp2 $sink2
$ns connect $udp3 $sink3

#Creates a TCPSink agent for n10, n11, n14, and n16
set tcpSink0 [new Agent/TCPSink]
set tcpSink1 [new Agent/TCPSink]
set tcpSink2 [new Agent/TCPSink]
set tcpSink3 [new Agent/TCPSink]
$ns attach-agent $n10 $tcpSink0
$ns attach-agent $n11 $tcpSink1
$ns attach-agent $n14 $tcpSink2
$ns attach-agent $n16 $tcpSink3

#Connects TCP sources to TCPSinks
$ns connect $tcp0 $tcpSink0
$ns connect $tcp1 $tcpSink1
$ns connect $tcp2 $tcpSink2
$ns connect $tcp3 $tcpSink3

#Schdeule of events
$ns at 1.0 "$cbr4 start"
$ns at 1.0 "$cbr5 start"
$ns at 1.0 "$cbr6 start"
$ns at 1.0 "$cbr7 start"
$ns at 2.0 "$cbr0 start"
$ns at 2.0 "$cbr1 start"
$ns at 2.0 "$cbr2 start"
$ns at 2.0 "$cbr3 start"
$ns rtmodel-at 6.0 down $n2 $n3
$ns rtmodel-at 7.0 up $n2 $n3
$ns at 10.0 "$cbr0 stop"
$ns at 10.0 "$cbr1 stop"
$ns at 10.0 "$cbr2 stop"
$ns at 10.0 "$cbr3 stop"
$ns at 10.0 "$cbr4 stop"
$ns at 10.0 "$cbr5 stop"
$ns at 10.0 "$cbr6 stop"
$ns at 10.0 "$cbr7 stop"
$ns at 11.0 "exit 0"

#Runs simulation
$ns run

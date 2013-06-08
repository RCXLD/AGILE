set val(chan)           Channel/WirelessChannel    ;# channel type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq
set node_num            5                         ;# number of mobilenodes
set val(rp)             AODV                       ;# routing protocol
set val(x)              1200  			   ;# X dimension of topography
set val(y)              1000   			   ;# Y dimension of topography
set energymodel EnergyModel
set energy_prx 0.4
set energy_psx 0.6
set energy_idle 0.3
set energy_initial 1000
set val(stop)		50			   ;# time of simulation end

set ns		  [new Simulator]
set tracefd       [open tracefile.tr w]
set namtrace      [open namtrace.nam w]
set energytrace	  [open energy.tr w]

$ns use-newtrace
$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

# set up topography object
set topo       [new Topography]

$topo load_flatgrid $val(x) $val(y)


create-god $node_num



$ns node-config -adhocRouting $val(rp) \
			 -llType $val(ll) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -ifqLen $val(ifqlen) \
			 -antType $val(ant) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -channel [new $val(chan)] \
			 -topoInstance $topo \
			 -agentTrace ON \
			 -routerTrace ON \
			 -macTrace ON \
			 -movementTrace OFF \
			-energyModel $energymodel \
			-rxPower $energy_prx \
			-txPower $energy_psx \
			-idlePower $energy_idle \
			-initialEnergy $energy_initial
 
for {set i 0} {$i < $node_num } { incr i } {
	set node_($i) [$ns node]	
}



$node_(0) set X_ 600.0
$node_(0) set Y_ 500.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 800.0
$node_(1) set Y_ 400.0
$node_(1) set Z_ 0.0

$node_(2) set X_ 1000.0
$node_(2) set Y_ 400.0
$node_(2) set Z_ 0.0

$node_(3) set X_ 800.0
$node_(3) set Y_ 600.0
$node_(3) set Z_ 0.0

$node_(4) set X_ 1000.0
$node_(4) set Y_ 600.0
$node_(4) set Z_ 0.0


set tcp [new Agent/TCP/Newreno]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns attach-agent $node_(0) $tcp
$ns attach-agent $node_(2) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at 1.0 "$ftp start" 

set udp_(0) [new Agent/UDP]
$udp_(0) set fid_ 1
$ns attach-agent $node_(0) $udp_(0)
set null_(0) [new Agent/Null]
$ns attach-agent $node_(4) $null_(0)

set cbr_(0) [new Application/Traffic/CBR]
$cbr_(0) set packetSize_ 200
$cbr_(0) set interval_ 0.01
$cbr_(0) set random_ 1
$cbr_(0) set maxpkts_ 10000
$cbr_(0) attach-agent $udp_(0)

$ns connect $udp_(0) $null_(0)
$ns at 10.0 "$cbr_(0) start"

for {set i 0} {$i < $node_num} { incr i } {
	$ns initial_node_pos $node_($i) 30
}

for {set i 0} {$i < $node_num } { incr i } {
    $ns at $val(stop) "$node_($i) reset";
}

$ns at $val(stop) "stop"
$ns at 0.0 "Record_Energy"
$ns at 100.0001 "puts \"end simulation\" ; $ns halt"


proc stop {} {
    global ns tracefd namtrace
    $ns flush-trace
    close $tracefd
    close $namtrace
}

proc Record_Energy {} {
	global ns energytrace node_num
	global opt node_
	set ns [Simulator instance]
	set Record_Inte 5
	set total_energy 0

	for {set j 0} {$j<$node_num} {incr j} {
		set Energy($j) [$node_($j) energy]
		set total_energy [expr $total_energy+$Energy($j)]
	}

	set now [$ns now]
	puts $energytrace "$now $total_energy"
	$ns at [expr $now+$Record_Inte] "Record_Energy"
}

$ns run

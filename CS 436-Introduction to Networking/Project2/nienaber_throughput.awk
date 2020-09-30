#Calculates throughput, number of packets sent, recieved, and lost for every 0.5 time interval for the 4 flows

BEGIN {
  time1 = 0.0;
  time2 = 0.0;
  timeInterval = 0.0;
  bytes_counter_flow0 = 0;
  bytes_counter_flow1 = 0;
  bytes_counter_flow2 = 0;
  bytes_counter_flow3 = 0;
}

{
  time2 = $2;

  timeInterval = time2 - time1;

  if (timeInterval > 0.5) {
    throughput_flow0 = bytes_counter_flow0 / timeInterval;
    throughput_flow1 = bytes_counter_flow1 / timeInterval;
    throughput_flow2 = bytes_counter_flow2 / timeInterval;
    throughput_flow3 = bytes_counter_flow3 / timeInterval;

    #Exports throughput of this time interval to xls file
    printf("%f \t %f \t %f \t %f \t %f \n", time2, throughput_flow0, throughput_flow1, throughput_flow2, throughput_flow3) > "nienaber_throughput.xls";
    bytes_counter_flow0 = 0;
    bytes_counter_flow1 = 0;
    bytes_counter_flow2 = 0;
    bytes_counter_flow3 = 0;

    time1 = $2;
  }

  #if the  packet that arrives at n10 belongs to flow id 0
  if ($1 == "r" && $4 == 10 && $8 == 0) {
    bytes_counter_flow0 += $6;
  }

  #if the  packet that arrives at n12 belongs to flow id 1
  if ($1 == "r" && $4 == 12 && $8 == 1) {
    bytes_counter_flow1 += $6;
  }

  #if the  packet that arrives at n14 belongs to flow id 2
  if ($1 == "r" && $4 == 14 && $8 == 2) {
    bytes_counter_flow2 += $6;
  }

  #if the  packet that arrives at n15 belongs to flow id 3
  if ($1 == "r" && $4 == 15 && $8 == 3) {
    bytes_counter_flow3 += $6;
  }

}

END {
    printf("****End of awk file****");
}

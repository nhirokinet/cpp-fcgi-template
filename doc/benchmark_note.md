# Environment

```
$ free -h
              total        used        free      shared  buff/cache   available
Mem:           5.8G        2.2G        2.1G        101M        1.5G        3.2G
Swap:          1.0G          0B        1.0G
```

```
$ cat /proc/cpuinfo 
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 61
model name	: Intel(R) Core(TM) i7-5600U CPU @ 2.60GHz
stepping	: 4
microcode	: 0x24
cpu MHz		: 2593.995
cache size	: 4096 KB
physical id	: 0
siblings	: 3
core id		: 0
cpu cores	: 3
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 20
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts nopl xtopology tsc_reliable nonstop_tsc aperfmperf eagerfpu pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch epb fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 invpcid rtm rdseed adx smap xsaveopt dtherm ida arat pln pts
bugs		:
bogomips	: 5187.99
clflush size	: 64
cache_alignment	: 64
address sizes	: 42 bits physical, 48 bits virtual
power management:

processor	: 1
vendor_id	: GenuineIntel
cpu family	: 6
model		: 61
model name	: Intel(R) Core(TM) i7-5600U CPU @ 2.60GHz
stepping	: 4
microcode	: 0x24
cpu MHz		: 2593.995
cache size	: 4096 KB
physical id	: 0
siblings	: 3
core id		: 1
cpu cores	: 3
apicid		: 1
initial apicid	: 1
fpu		: yes
fpu_exception	: yes
cpuid level	: 20
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts nopl xtopology tsc_reliable nonstop_tsc aperfmperf eagerfpu pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch epb fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 invpcid rtm rdseed adx smap xsaveopt dtherm ida arat pln pts
bugs		:
bogomips	: 5187.99
clflush size	: 64
cache_alignment	: 64
address sizes	: 42 bits physical, 48 bits virtual
power management:

processor	: 2
vendor_id	: GenuineIntel
cpu family	: 6
model		: 61
model name	: Intel(R) Core(TM) i7-5600U CPU @ 2.60GHz
stepping	: 4
microcode	: 0x24
cpu MHz		: 2593.995
cache size	: 4096 KB
physical id	: 0
siblings	: 3
core id		: 2
cpu cores	: 3
apicid		: 2
initial apicid	: 2
fpu		: yes
fpu_exception	: yes
cpuid level	: 20
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts nopl xtopology tsc_reliable nonstop_tsc aperfmperf eagerfpu pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch epb fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 invpcid rtm rdseed adx smap xsaveopt dtherm ida arat pln pts
bugs		:
bogomips	: 5187.99
clflush size	: 64
cache_alignment	: 64
address sizes	: 42 bits physical, 48 bits virtual
power management:
```

# Result

```
$ ab -c 10 -t 10 'http://localhost/myapi/kvs?Rabc' & ab -c 10 -t 10 'http://localhost/myapi/kvs?Wabc&def'
[1] 85695
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 5000 requests
Completed 5000 requests
Completed 10000 requests
Completed 10000 requests
Completed 15000 requests
Completed 15000 requests
Completed 20000 requests
Completed 20000 requests
Completed 25000 requests
Completed 25000 requests
Completed 30000 requests
Completed 30000 requests
Completed 35000 requests
Completed 35000 requests
Completed 40000 requests
Completed 40000 requests
Completed 45000 requests
Completed 45000 requests
Finished 46671 requests


Server Software:        nginx/1.10.3
Server Hostname:        localhost
Server Port:            80

Document Path:          /myapi/kvs?Wabc&def
Document Length:        2 bytes

Concurrency Level:      10
Time taken for tests:   10.001 seconds
Complete requests:      46671
Failed requests:        0
Total transferred:      6253914 bytes
HTML transferred:       93342 bytes
Requests per second:    4666.53 [#/sec] (mean)
Time per request:       2.143 [ms] (mean)
Time per request:       0.214 [ms] (mean, across all concurrent requests)
Transfer rate:          610.66 [Kbytes/sec] received
Finished 47069 requests


Server Software:        nginx/1.10.3
Server Hostname:        localhost
Server Port:            80

Document Path:          /myapi/kvs?Rabc
Document Length:        3 bytes

Concurrency Level:      10
Time taken for tests:   10.003 seconds
Complete requests:      47069
Failed requests:        0
Total transferred:      6354315 bytes
HTML transferred:       141207 bytes
Requests per second:    4705.33 [#/sec] (mean)
Time per request:       2.125 [ms] (mean)
Time per request:       0.213 [ms] (mean, across all concurrent requests)
Transfer rate:          620.33 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.3      0      17
Processing:     0    2   1.7      2      30
Waiting:        0    2   1.6      2      28
Total:          0    2   1.7      2      30

Percentage of the requests served within a certain time (ms)
  50%      2
  66%      2
  75%      2
  80%      2
  90%      3
  95%      4
  98%      8
  99%     10
 100%     30 (longest request)

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.3      0      13
Processing:     0    2   1.7      2      29
Waiting:        0    2   1.6      2      29
Total:          0    2   1.7      2      36

Percentage of the requests served within a certain time (ms)
  50%      2
  66%      2
  75%      2
  80%      2
  90%      3
  95%      5
  98%      8
  99%     10
 100%     36 (longest request)
[1]+  Done                    ab -c 10 -t 10 'http://localhost/myapi/kvs?Rabc'
```

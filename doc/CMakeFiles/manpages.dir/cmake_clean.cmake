file(REMOVE_RECURSE
  "AUTHORS-SHORT"
  "AUTHORS-SHORT-FORMAT"
  "CMakeFiles/manpages"
  "androiddump.1"
  "capinfos.1"
  "captype.1"
  "ciscodump.1"
  "dftest.1"
  "dpauxmon.1"
  "dumpcap.1"
  "editcap.1"
  "extcap.4"
  "mergecap.1"
  "mmdbresolve.1"
  "randpkt.1"
  "randpktdump.1"
  "rawshark.1"
  "reordercap.1"
  "sdjournal.1"
  "sshdump.1"
  "text2pcap.1"
  "tshark.1"
  "udpdump.1"
  "wireshark-filter.4"
  "wireshark.1"
  "wireshark.pod"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/manpages.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

# TLSF+TECS

Component-based TLSF, dynamic memory allocator for embedded systems

## TLSF (Two-Level Segregate Fit)

TLSF is a dynamic memory allocator suitable for embedded systems.
TLSF improves memory utilization efficiency by finely dividing memory blocks into two stages.
The worst execution time can be estimated because it is always executed with O(1).
TLSF memory allocator is suitable for real-time systems, so it is adopted in many RTOSs.


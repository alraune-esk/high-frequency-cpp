# High-Frequency-Cpp



## Purpose:

To explore and learn more about some software design patterns of low-latency programming with **C++** that may typically be used in a **High-Frequency Trading** context.
General details of these techniques were scoured from publicly available resources, noting that most if not all actual algorithms and techniques used by HFT companies would be kept private.


## Techniques explored:

 - **Cache-warming**
 - **Lock-free programming**
 - **SIMD**
 - **Signed and unsigned INTs**
 - **Prefetching**
 - **Branch Reduction**
 - **Loop unrolling**



Each can be run separately and displays relevant execution times averaged over some sample of runs.
The aim is to implement these techniques within the context of a simplified HFT trading algorithm. Market data would be randomly generated as input with core logic being simulated alongside low-latency techniques. 
Network latency, more specifically optimisation of network latency is a key aspect of HFT, I've introduced this with a simple latency generator that uses slight deviations on estimated latency times to locations around the world that will vary over time.



## To Explore:



 - More detail with incorporation of simulated market data and network 
   latency values.
 - Patterns and considerations for data transfers, depending on latency 
   and time to run core logic what method of data  transfer is optimal?
   
 - Other areas to incorporate optimisations and design patterns for lower latency, such as other core aspects of HFT such as risk management and API interactions.
 - Quantitative analysis of improvement using low latency techniques, i.e. How many more buy sell signals can be generated and quantified what increase in revenue does this translate to?

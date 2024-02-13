# high-frequency-cpp

Purpose:
To explore and demonstrate a practical application of techniques and design patterns for Low-Latency applications with a focus on High-Frequency Trading context.

Techniques explored:
Use of constexpr
Cache-warming
Loop unrolling
Short-circuiting

These techniques are implemented within the context of a simplified High-Frequency Trading algorithm.
Signals, such as stock price are randomly generated as input.
Network latency is also incorporated with slight deviations from average latency values over time.
Locations considered are APAC and countries with Optiver physical offices.

Evaluation:
Each technique is implemented in isolation and timed. External data (stock price and network latency values) are kept the same for each run. 
A full run with all of the above techniques is also done.
Timed and averaged over 10 runs.


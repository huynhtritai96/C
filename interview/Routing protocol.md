### **What Do Routing Protocols Do?**
---
### **Routing Protocol Examples**

1. **RIP (Routing Information Protocol)**:
   - **Type**: Distance-vector protocol.
   - **Metric**: Hop count.
   - **Max Hop Count**: 15 hops (16 is considered unreachable).
   - **Use Case**: Simple, small networks due to its slow convergence and limited scalability.

2. **OSPF (Open Shortest Path First)**:
   - **Type**: Link-state protocol.
   - **Metric**: Cost, based on link bandwidth.
   - **Algorithm**: Dijkstra's shortest path first (SPF).
   - **Use Case**: Large enterprise networks requiring fast convergence and scalability.

---   

**Routing protocols** are essential mechanisms used by routers to discover, maintain, and update **routes** in a network. Their primary role is to ensure that routers can **dynamically** and **efficiently** determine the best path for data packets to travel across interconnected networks, which is essential for communication in complex and large-scale networks such as the internet. 

Routing protocols facilitate the automatic sharing of routing information between routers and make decisions about which route to use based on specific metrics (e.g., hop count, bandwidth, delay).

### **Key Functions of Routing Protocols**

1. **Discover Network Topology**:
   - Routing protocols enable routers to automatically discover the topology of the network, including the routers and networks that are reachable through them. This allows routers to dynamically adapt to changes in the network, such as new routers being added or removed.

2. **Share Routing Information**:
   - Routers use routing protocols to **exchange information** about available routes with neighboring routers. By sharing this information, each router can build and maintain a **routing table** containing the best paths to various destination networks.

3. **Select the Best Route**:
   - Routing protocols determine the **best path** (or "optimal route") for forwarding packets based on various **metrics**. These metrics might include:
     - **Hop count**: The number of routers a packet must pass through to reach its destination.
     - **Bandwidth**: The available bandwidth on a path.
     - **Delay**: The time it takes for a packet to traverse the path.
     - **Cost**: A configurable value that reflects the preference of using a particular route.
   - Routing protocols ensure that routers use the best available path based on these metrics.

4. **Maintain Routing Tables**:
   - Routers use routing protocols to keep their **routing tables** updated. Routing tables store the paths to various destination networks, along with associated metrics, and are used to forward packets.
   - Routing protocols regularly update the routing tables to reflect changes in the network, such as link failures or topology changes.

5. **Adapt to Network Changes**:
   - When network changes occur (e.g., a link failure, a router going down, or a new network being added), routing protocols allow routers to **recalculate** the best paths and update their routing tables. This process is known as **convergence**, and it's essential for maintaining accurate and up-to-date routing information.

6. **Prevent Routing Loops**:
   - Some routing protocols implement mechanisms to prevent **routing loops**, which occur when packets circulate endlessly between routers without reaching their destination. Techniques like **split horizon**, **route poisoning**, and **hold-down timers** help prevent these loops.

7. **Support Redundancy and Load Balancing**:
   - Routing protocols can support **redundancy** by enabling routers to maintain multiple paths to the same destination. If the primary path fails, an alternative path can be used. Some routing protocols also support **load balancing**, where traffic is distributed across multiple paths to optimize network performance.

---

### **Types of Routing Protocols**

Routing protocols are classified into different types based on various criteria, such as how they share routing information and the scope of the network they operate in.

#### **1. Interior Gateway Protocols (IGPs)**
- **Interior Gateway Protocols (IGPs)** are used within a single **autonomous system (AS)**, such as an organization's internal network. IGPs share routing information between routers in the same AS.
  
- **Examples of IGPs**:
  - **RIP (Routing Information Protocol)**: A distance-vector routing protocol that uses **hop count** as the metric to determine the best route. It is simple but limited to smaller networks because of its slow convergence and maximum hop count (15 hops).
  - **OSPF (Open Shortest Path First)**: A link-state routing protocol that uses the **Dijkstra algorithm** to compute the shortest path. It is highly scalable and used in large, complex networks.
  - **EIGRP (Enhanced Interior Gateway Routing Protocol)**: A Cisco proprietary protocol that combines the features of both distance-vector and link-state protocols. It uses **composite metrics** (bandwidth, delay, reliability, and load) to determine the best path.

#### **2. Exterior Gateway Protocols (EGPs)**
- **Exterior Gateway Protocols (EGPs)** are used to exchange routing information between routers in different **autonomous systems (AS)**, typically between organizations or Internet Service Providers (ISPs).

- **Example of EGP**:
  - **BGP (Border Gateway Protocol)**: The primary protocol used to route traffic between different autonomous systems on the **internet**. BGP is a **path-vector protocol**, and it is responsible for making decisions based on path attributes and policies. BGP is highly scalable and essential for inter-AS routing.

---

### **How Routing Protocols Work**

Routing protocols operate by using specific algorithms to manage and propagate routing information between routers. The two main classes of routing algorithms are **distance-vector** and **link-state** algorithms. Some protocols combine these methods for hybrid behavior.

#### **1. Distance-Vector Routing Protocols**
- Distance-vector protocols use a simple metric such as **hop count** to determine the best path to a destination. Each router only knows about its **direct neighbors** and the distance (metric) to reach a particular destination.
- Routers using distance-vector protocols share their routing table with neighbors, and each router **trusts** its neighbors' knowledge of the network.

- **Example**: **RIP (Routing Information Protocol)**:
  - RIP periodically sends its routing table to all neighboring routers.
  - The routing table contains the destination networks and the number of hops to each destination.
  - Routers update their tables based on the information received from their neighbors, incrementing the hop count by 1 for each neighbor.
  - The route with the lowest hop count is selected as the best route.

#### **2. Link-State Routing Protocols**
- Link-state protocols have a more comprehensive view of the network. Each router independently calculates the **shortest path** to every destination based on its knowledge of the entire network topology.
- Routers exchange **link-state advertisements (LSAs)** to build a complete view of the network, and each router uses a **shortest path first (SPF)** algorithm (such as **Dijkstra's algorithm**) to compute the best path.

- **Example**: **OSPF (Open Shortest Path First)**:
  - OSPF routers maintain a **link-state database** (LSDB) of the entire network.
  - Each router independently calculates the shortest path tree using the SPF algorithm.
  - OSPF supports **hierarchical routing** and allows for multiple **areas** to reduce the complexity of large networks.

#### **3. Hybrid Routing Protocols**
- Hybrid protocols combine the features of both distance-vector and link-state protocols to improve scalability and efficiency.

- **Example**: **EIGRP (Enhanced Interior Gateway Routing Protocol)**:
  - EIGRP uses distance-vector techniques but incorporates some link-state features like **partial updates** and **triggered updates**, meaning that only changes to the network are propagated, reducing overhead.

---

### **Key Metrics Used by Routing Protocols**

Routing protocols use different **metrics** to determine the best path to a destination. Common metrics include:

- **Hop Count**: The number of routers (hops) a packet must pass through to reach the destination.
  - **Example**: RIP uses hop count as its only metric, with a maximum limit of 15 hops.
  
- **Bandwidth**: The data capacity of a link. Higher bandwidth links are preferred over lower bandwidth links.
  - **Example**: EIGRP uses bandwidth as one of its metrics.

- **Delay**: The time it takes for a packet to traverse a link. Lower delays are preferred.
  - **Example**: EIGRP considers delay when calculating routes.

- **Cost**: A configurable value assigned to a link. The cost can be based on various factors, such as bandwidth or administrative preference.
  - **Example**: OSPF uses cost as the metric, with lower cost links being preferred.

- **Load**: The amount of traffic currently on the link. Less-loaded links are preferred.
  - **Example**: EIGRP can use load as a metric.

- **Reliability**: The stability or error rate of a link. More reliable links are preferred.
  - **Example**: EIGRP uses reliability as one of its metrics.

---

### **Convergence in Routing Protocols**

**Convergence** refers to the state where all routers in a network have the same, up-to-date routing information. Routing protocols work to **quickly converge** after a network change, such as a link failure, by updating their routing tables with new information. 

- **Fast Convergence** is a desirable property of a routing protocol because it reduces the time during which packets may be lost or misrouted due to outdated routing information.

- **Link-State Protocols** like **OSPF** tend to converge faster than **distance-vector protocols** like **RIP** because they propagate detailed topology changes rather than entire routing tables.

---

### **Routing Protocol Examples**

1. **RIP (Routing Information Protocol)**:
   - **Type**: Distance-vector protocol.
   - **Metric**: Hop count.
   - **Max Hop Count**: 15 hops (16 is considered unreachable).
   - **Use Case**: Simple, small networks due to its slow convergence and limited scalability.

2. **OSPF (Open Shortest Path First)**:
   - **Type**: Link-state protocol.
   - **Metric**: Cost, based on link bandwidth.
   - **Algorithm**: Dijkstra's shortest path first (SPF).
   - **Use Case**: Large enterprise networks requiring fast convergence and scalability.

3. **EIGRP (Enhanced Interior Gateway Routing Protocol)**:
   - **Type**: Hybrid protocol (combines distance-vector and link-state features).
   - **Metric**: Composite metric (bandwidth, delay, load, reliability).
   - **Algorithm**: Diffusing Update Algorithm (DUAL).
   - **Use Case**: Medium to large Cisco-based networks requiring scalability and fast convergence.

4. **BGP (Border Gateway Protocol)**:
   - **Type**: Path-vector protocol.
   - **Metric**: Path attributes (AS-path, next hop, etc.).
   - **Use Case**: Internet routing between autonomous systems, ISPs.

---

### **Conclusion**

Routing protocols play a critical role in ensuring that routers can dynamically discover, select, and maintain the best paths for forwarding data across networks. They are essential for scalability, flexibility, and reliability in modern, large-scale networks. Routing protocols like **RIP**, **OSPF**, **EIGRP**, and **BGP** provide the intelligence that routers need to adapt to changes in the network, ensuring that data reaches its destination efficiently and reliably.
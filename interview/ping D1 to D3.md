### **Network Topology**:  
We will set up a simple network topology with two switches, two routers, and four PCs. The layout is as follows:

1. **Switch 1** connects **PC A** and **PC B**.
2. **Router 1** connects to **Switch 1** and to **Router 2**.
3. **Router 2** connects to **Switch 2**.
4. **Switch 2** connects **PC C** and **PC D**.

#### **IP Addressing Scheme**:

- **PC A (PCA)**: `192.168.1.10/24`
- **PC B (PCB)**: `192.168.1.11/24`
- **Router 1 Interface to Switch 1**: `192.168.1.1/24`
- **Router 1 Interface to Router 2**: `10.0.0.1/30`
- **Router 2 Interface to Router 1**: `10.0.0.2/30`
- **Router 2 Interface to Switch 2**: `192.168.2.1/24`
- **PC C (PCC)**: `192.168.2.10/24`
- **PC D (PCD)**: `192.168.2.11/24`

---

### **Step-by-Step Network Layout**

1. **PC A and PC B** are in the **192.168.1.0/24** network and connect to **Switch 1**.
2. **Router 1** connects **Switch 1** via its interface `192.168.1.1/24` and to **Router 2** via the point-to-point link `10.0.0.1/30`.
3. **Router 2** connects to **Router 1** via `10.0.0.2/30` and connects to **Switch 2** via the `192.168.2.1/24` interface.
4. **PC C and PC D** are in the **192.168.2.0/24** network and connect to **Switch 2**.

---

### **Routing Tables for Each Device**

Now, let’s configure the routing tables for each device in the network.

#### **1. PC A (PCA) Routing Table**
Since PC A is connected to **Switch 1** in the **192.168.1.0/24** network, its routing table will look like this:

| Destination      | Subnet Mask     | Gateway      | Interface |
|------------------|-----------------|--------------|-----------|
| `192.168.1.0`    | `255.255.255.0` | `0.0.0.0`    | `eth0`    |
| `0.0.0.0`        | `0.0.0.0`       | `192.168.1.1`| `eth0`    |

- **Explanation**:
  - PC A has a route to the **local network** (`192.168.1.0/24`).
  - The **default route** (for all other destinations) is forwarded to the **gateway** (Router 1 at `192.168.1.1`).

#### **2. PC B (PCB) Routing Table**
Similarly, PC B is in the **192.168.1.0/24** network, and its routing table will be identical to PC A:

| Destination      | Subnet Mask     | Gateway      | Interface |
|------------------|-----------------|--------------|-----------|
| `192.168.1.0`    | `255.255.255.0` | `0.0.0.0`    | `eth0`    |
| `0.0.0.0`        | `0.0.0.0`       | `192.168.1.1`| `eth0`    |

- **Explanation**:
  - PC B has a route to its **local network** (`192.168.1.0/24`).
  - Any traffic for destinations outside the local network is sent to Router 1's interface (`192.168.1.1`).

#### **3. Router 1 Routing Table**
Router 1 connects **Switch 1** (network `192.168.1.0/24`) to **Router 2** via a point-to-point link (`10.0.0.0/30`). Router 1 also needs a route to the **192.168.2.0/24** network on the other side of Router 2.

| Destination      | Subnet Mask     | Gateway      | Interface  |
|------------------|-----------------|--------------|------------|
| `192.168.1.0`    | `255.255.255.0` | `0.0.0.0`    | `eth0`     |
| `10.0.0.0`       | `255.255.255.252`| `0.0.0.0`   | `eth1`     |
| `192.168.2.0`    | `255.255.255.0` | `10.0.0.2`   | `eth1`     |
| `0.0.0.0`        | `0.0.0.0`       | `10.0.0.2`   | `eth1`     |

- **Explanation**:
  - **Directly connected networks**:
    - **192.168.1.0/24** is directly connected to **Switch 1** via interface `eth0`.
    - **10.0.0.0/30** is the point-to-point link between Router 1 and Router 2 via `eth1`.
  - Router 1 needs a static route to the **192.168.2.0/24** network, which is accessible via Router 2’s interface (`10.0.0.2`).
  - The **default route** sends all other traffic to Router 2 via `10.0.0.2`.

#### **4. Router 2 Routing Table**
Router 2 connects the point-to-point link (`10.0.0.0/30`) to the **192.168.2.0/24** network via **Switch 2**. It also needs a route back to the **192.168.1.0/24** network on the other side of Router 1.

| Destination      | Subnet Mask     | Gateway      | Interface  |
|------------------|-----------------|--------------|------------|
| `192.168.2.0`    | `255.255.255.0` | `0.0.0.0`    | `eth0`     |
| `10.0.0.0`       | `255.255.255.252`| `0.0.0.0`   | `eth1`     |
| `192.168.1.0`    | `255.255.255.0` | `10.0.0.1`   | `eth1`     |
| `0.0.0.0`        | `0.0.0.0`       | `10.0.0.1`   | `eth1`     |

- **Explanation**:
  - **Directly connected networks**:
    - **192.168.2.0/24** is directly connected to **Switch 2** via `eth0`.
    - **10.0.0.0/30** is the point-to-point link to Router 1 via `eth1`.
  - Router 2 needs a static route to the **192.168.1.0/24** network via Router 1’s interface (`10.0.0.1`).
  - The **default route** sends all other traffic back to Router 1 (`10.0.0.1`).

#### **5. PC C (PCC) Routing Table**
PC C is in the **192.168.2.0/24** network, connected to **Switch 2**. Its routing table is similar to that of PC A and PC B, but it uses **Router 2** as its default gateway.

| Destination      | Subnet Mask     | Gateway      | Interface |
|------------------|-----------------|--------------|-----------|
| `192.168.2.0`    | `255.255.255.0` | `0.0.0.0`    | `eth0`    |
| `0.0.0.0`        | `0.0.0.0`       | `192.168.2.1`| `eth0`    |

- **Explanation**:
  - PC C can communicate with the **local network** (`192.168.2.0/24`) directly.
  - Any traffic for external networks (like `192.168.1.0/24`) is sent to Router 2 (`192.168.2.1`).

#### **6. PC D (PCD) Routing Table**
Similarly, PC D is in the **192.168.2.0/24** network, so its routing table mirrors PC C's.

| Destination      | Subnet Mask     | Gateway      | Interface |
|------------------|-----------------|--------------|-----------|
| `192.168.2.0`    | `255.255.255.0` | `0.0.0.0`    | `eth0`    |
| `

0.0.0.0`        | `0.0.0.0`       | `192.168.2.1`| `eth0`    |

- **Explanation**:
  - PC D can communicate with the local network (`192.168.2.0/24`) directly.
  - For external traffic, it sends packets to Router 2 (`192.168.2.1`).

---

### **Routing Workflow Example**

If **PC A** (IP: `192.168.1.10`) wants to ping **PC C** (IP: `192.168.2.10`), the process works as follows:

1. **PC A** checks its routing table and sees that **192.168.2.0/24** is not in the local subnet. It sends the packet to its **default gateway** (`192.168.1.1`), which is Router 1.
   
2. **Router 1** checks its routing table and sees that traffic for the **192.168.2.0/24** network should be forwarded to **Router 2** at `10.0.0.2`.

3. **Router 2** receives the packet and checks its routing table. It sees that the **192.168.2.0/24** network is directly connected via its interface `eth0`.

4. **Router 2** forwards the packet to **PC C**.

5. **PC C** responds to the ping, and the reply follows the same path in reverse:
   - PC C sends the reply to its gateway (**Router 2**, `192.168.2.1`).
   - Router 2 forwards it to Router 1 (`10.0.0.1`).
   - Router 1 forwards it to PC A (`192.168.1.10`).

---

### **Summary**

The routing tables for each device enable them to forward packets based on the destination IP address. In this network, each device has a combination of direct routes (for their local subnet) and static or dynamic routes for reaching other subnets through routers. This allows PC A and PC B (in `192.168.1.0/24`) to communicate with PC C and PC D (in `192.168.2.0/24`) via Router 1 and Router 2.
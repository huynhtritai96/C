
# ARP Protocol (Address Resolution Protocol)

# [Q] Why do we need an IP address if we already have a MAC address in computer networks?
https://medium.com/@bedmuthaapoorv/why-do-we-need-an-ip-address-if-we-already-have-a-mac-address-in-computer-networks-310a9611743a

Because: Source IP and Destination IP does not change during the transaction, but it changes the Source MAC and Destination MAC based on routing tables

### **Summary of MAC and IP Address Usage in This Extended Setup**

1. **Computer A (192.168.1.10) to Router 1 (192.168.1.1)**:
   - **Source MAC**: `AA:AA:AA:AA:AA:AA` (Computer A)
   - **Destination MAC**: `R1:R1:R1:R1:R1:R1` (Router 1's Interface 1)
   - **Source IP**: `192.168.1.10` (Computer A)
   - **Destination IP**: `192.168.2.10` (Computer C)

2. **Router 1 (10.0.0.1) to Router 2 (10.0.0.2)**:
   - **Source MAC**: `R2:R2:R2:R2:R2:R2` (Router 1's Interface 2)
   - **Destination MAC**: `R3:R3:R3:R3:R3:R3` (Router 2's Interface 1)
   - **Source IP**: `192.168.1.10` (Computer A)
   - **Destination IP**: `192.168.2.10` (Computer C)

3. **Router 2 (192.168.2.1) to Computer C (192.168.2.10)**:
   - **Source MAC**: `R4:R4:R4:R4:R4:R4` (Router 2's Interface 2)
   - **Destination MAC**: `CC:CC:CC:CC:CC:CC` (Computer C)
   - **Source IP**: `192.168.1.10` (Computer A)
   - **Destination IP**: `192.168.2.10` (Computer C)

# [Q] MAC and IP address have ARP tables, routing of router have routing table for IP, anything else for routing?


### **ARP Protocol (Address Resolution Protocol)**

**ARP (Address Resolution Protocol)** is a network protocol used to map a **network layer address** (IP address) to a **link layer address** (MAC address). It is essential for communication within a local network, where devices need to find the physical address of a destination device corresponding to an IP address.

ARP operates within **Layer 2 (Data Link layer)** of the OSI model and is used by network devices such as routers, switches, and computers to identify the **MAC address** of a device when only its **IP address** is known. ARP is mainly used in **IPv4 networks**.

### **How ARP Works**

The ARP process involves **two main message types**:
1. **ARP Request**: A broadcast message that asks for the MAC address of a device with a specific IP address.
2. **ARP Reply**: A unicast response that provides the MAC address of the requested IP address.

#### **Step-by-Step Explanation of ARP Process**:

1. **Device A wants to communicate with Device B** but knows only Device B's **IP address** (say `192.168.1.2`). Device A does not know the **MAC address** of Device B.

2. **ARP Request**:
   - Device A constructs an **ARP Request** packet that includes its own **IP and MAC address**, as well as the **target IP address** (`192.168.1.2`) whose MAC address it wants to find.
   - This ARP Request is then **broadcasted** to all devices on the local network because Device A does not know which device has that IP address.
   - The broadcast address used is `FF:FF:FF:FF:FF:FF` (broadcast MAC address) at Layer 2, meaning all devices in the local network will receive this packet.

3. **Device B receives the ARP Request** because it is part of the same network. Device B checks the ARP Request and sees that the **requested IP address matches its own IP** (`192.168.1.2`).

4. **ARP Reply**:
   - Device B constructs an **ARP Reply** packet containing its own **MAC address**.
   - The ARP Reply is sent **directly (unicast)** to Device A's MAC address.
   
5. **Device A receives the ARP Reply** with Device B's **MAC address** and stores this mapping (IP-to-MAC) in its **ARP cache** for future use. Device A can now send data to Device B using its MAC address.

6. **Subsequent communication**: For future communications, Device A does not need to send another ARP Request for Device B's IP address as long as the ARP cache entry is valid.

---

### **ARP Packet Format**

An ARP packet contains several fields:
- **Hardware Type**: Specifies the type of hardware (Ethernet is 1).
- **Protocol Type**: Specifies the protocol being used (IPv4 is `0x0800`).
- **Hardware Address Length**: Length of the hardware address (MAC address, typically 6 bytes).
- **Protocol Address Length**: Length of the protocol address (IP address, typically 4 bytes).
- **Operation**: Specifies whether the packet is a request (1) or a reply (2).
- **Sender MAC Address**: MAC address of the sender.
- **Sender IP Address**: IP address of the sender.
- **Target MAC Address**: MAC address of the target (set to 0 in the ARP request).
- **Target IP Address**: IP address of the target.

---

### **ARP Example**

- Device A (IP: `192.168.1.1`, MAC: `AA:AA:AA:AA:AA:AA`) wants to communicate with Device B (IP: `192.168.1.2`) on the same local network.
  
#### **ARP Request** (sent by Device A):
```
Sender MAC: AA:AA:AA:AA:AA:AA
Sender IP: 192.168.1.1
Target MAC: FF:FF:FF:FF:FF:FF (broadcast)
Target IP: 192.168.1.2
```

#### **ARP Reply** (sent by Device B):
```
Sender MAC: BB:BB:BB:BB:BB:BB
Sender IP: 192.168.1.2
Target MAC: AA:AA:AA:AA:AA:AA
Target IP: 192.168.1.1
```

---

### **ARP Cache**

To avoid sending ARP requests for every packet, devices maintain an **ARP cache**, which is a table that stores IP-to-MAC address mappings. Entries in the ARP cache are typically time-limited and will expire after a certain period.

#### **Viewing ARP Cache**:
On most systems, you can view the ARP cache with the following command:
```bash
arp -a
```

---

### **Types of ARP**

1. **Proxy ARP**: A router replies to an ARP Request on behalf of another device, allowing communication across different networks.
2. **Gratuitous ARP**: A device sends an ARP Request for its own IP address to update the ARP caches of other devices (often used for duplicate address detection or notifying the network of a MAC address change).
3. **Reverse ARP (RARP)**: An older protocol used by devices to request their own IP address from a server when they only know their MAC address (obsolete, replaced by DHCP).

---

### **ARP in Different Scenarios**

- **IPv4 Address Resolution**: ARP is used to find the MAC address corresponding to an IPv4 address on a local network.
- **Router Communication**: When a host sends data to a destination outside its local network, it first ARPs to find the MAC address of its **default gateway** (router) and sends the packet to that router.

---

### **ARP Spoofing (ARP Poisoning)**

**ARP Spoofing** is a type of attack where a malicious device sends false ARP replies, associating its MAC address with the IP address of another device (e.g., the gateway). This allows the attacker to intercept, modify, or block communication between devices.

#### **How ARP Spoofing Works**:
1. The attacker sends forged ARP replies to a target, making the target believe the attacker's MAC address corresponds to a legitimate IP address (like the default gateway).
2. As a result, traffic meant for the legitimate IP address is sent to the attacker instead.

#### **Mitigation**:
- **Static ARP entries**: Assigning fixed IP-to-MAC address mappings.
- **ARP monitoring tools**: Detecting abnormal ARP traffic.
- **Dynamic ARP Inspection (DAI)**: A security feature on switches that validates ARP packets.

---

### **Conclusion**

---

Sure! Let’s break down an example of **routing** that involves **MAC addresses** and **IP addresses** with two switches, each having two computers connected, and a **router** between the switches. This example will demonstrate how communication works both at the **network layer (IP addresses)** and the **data link layer (MAC addresses)**.

### **Network Topology Setup**

- **Switch 1**:
  - Computer A (`IP: 192.168.1.10`, `MAC: AA:AA:AA:AA:AA:AA`)
  - Computer B (`IP: 192.168.1.11`, `MAC: BB:BB:BB:BB:BB:BB`)

- **Switch 2**:
  - Computer C (`IP: 192.168.2.10`, `MAC: CC:CC:CC:CC:CC:CC`)
  - Computer D (`IP: 192.168.2.11`, `MAC: DD:DD:DD:DD:DD:DD`)

- **Router** between Switch 1 and Switch 2:
  - **Router Interface 1 (connected to Switch 1)**: `IP: 192.168.1.1`, `MAC: R1:R1:R1:R1:R1:R1`
  - **Router Interface 2 (connected to Switch 2)**: `IP: 192.168.2.1`, `MAC: R2:R2:R2:R2:R2:R2`

### **Objective**:
- Computer A on **Switch 1** (`192.168.1.10`) wants to communicate with Computer C on **Switch 2** (`192.168.2.10`).
  
### **Steps Involved**:

1. **Computer A (192.168.1.10) sends data to Computer C (192.168.2.10)**:
   - **Source**: Computer A (IP: `192.168.1.10`, MAC: `AA:AA:AA:AA:AA:AA`)
   - **Destination**: Computer C (IP: `192.168.2.10`)

### **Step-by-Step Process** (with MAC and IP addresses):

#### **1. Computer A checks if Computer C is on the same network (subnet)**:
- **Computer A** (192.168.1.10) and **Computer C** (192.168.2.10) are on **different subnets** (`192.168.1.x` and `192.168.2.x`).
- Computer A knows it needs to send the packet to its **default gateway** (Router's Interface 1) because Computer C is on a different network.

#### **2. ARP Request from Computer A to find Router's MAC address**:
- Computer A checks its ARP cache and sees that it does not have the MAC address of the **default gateway** (`192.168.1.1`).
- Computer A sends an **ARP Request**:
  - **Who has IP 192.168.1.1? Tell 192.168.1.10.**
  - This ARP request is broadcasted on the local network (Switch 1).
  
#### **3. Router responds with its MAC address**:
- The router's **Interface 1** (`192.168.1.1`) responds with its **MAC address** (`R1:R1:R1:R1:R1:R1`).
- Computer A stores the IP-to-MAC mapping of the router in its ARP cache:
  - **192.168.1.1 -> R1:R1:R1:R1:R1:R1**

#### **4. Computer A sends the packet to Router**:
- Computer A prepares an Ethernet frame with:
  - **Source MAC**: `AA:AA:AA:AA:AA:AA` (Computer A)
  - **Destination MAC**: `R1:R1:R1:R1:R1:R1` (Router Interface 1)
  - **Source IP**: `192.168.1.10` (Computer A)
  - **Destination IP**: `192.168.2.10` (Computer C)
  
- The packet is forwarded to **Router Interface 1** (connected to Switch 1).

#### **5. Router receives the packet and forwards it**:
- The router receives the packet, reads the **IP address** (`192.168.2.10`), and realizes that the packet must be forwarded to **Switch 2** via its **Interface 2** (`192.168.2.1`).
  
- The router **replaces the Layer 2 information** (MAC addresses) to forward the packet:
  - **Source MAC**: `R2:R2:R2:R2:R2:R2` (Router Interface 2)
  - **Destination MAC**: **(needs Computer C's MAC)**

#### **6. ARP Request from Router to find Computer C's MAC address**:
- Router Interface 2 does not have Computer C's MAC address in its ARP cache, so it sends an **ARP Request**:
  - **Who has IP 192.168.2.10? Tell 192.168.2.1.**
  
- This ARP request is broadcasted on **Switch 2**.

#### **7. Computer C responds with its MAC address**:
- Computer C (IP: `192.168.2.10`, MAC: `CC:CC:CC:CC:CC:CC`) responds with an **ARP Reply**:
  - **I am 192.168.2.10, and my MAC address is CC:CC:CC:CC:CC:CC.**
  
- The router stores this IP-to-MAC mapping in its ARP cache:
  - **192.168.2.10 -> CC:CC:CC:CC:CC:CC**

#### **8. Router forwards the packet to Computer C**:
- The router rewrites the Ethernet frame to:
  - **Source MAC**: `R2:R2:R2:R2:R2:R2` (Router Interface 2)
  - **Destination MAC**: `CC:CC:CC:CC:CC:CC` (Computer C)
  - **Source IP**: `192.168.1.10` (Computer A)
  - **Destination IP**: `192.168.2.10` (Computer C)

- The router sends the packet to **Computer C** through **Switch 2**.

#### **9. Computer C receives the packet**:
- Computer C receives the packet, checks that the destination IP address matches its own (`192.168.2.10`), and processes the data.

### **Summary of MAC and IP Address Usage in the Process**

1. **Computer A (192.168.1.10) to Router Interface 1 (192.168.1.1)**:
   - **Source MAC**: `AA:AA:AA:AA:AA:AA`
   - **Destination MAC**: `R1:R1:R1:R1:R1:R1`
   - **Source IP**: `192.168.1.10`
   - **Destination IP**: `192.168.2.10`

2. **Router Interface 2 (192.168.2.1) to Computer C (192.168.2.10)**:
   - **Source MAC**: `R2:R2:R2:R2:R2:R2`
   - **Destination MAC**: `CC:CC:CC:CC:CC:CC`
   - **Source IP**: `192.168.1.10`
   - **Destination IP**: `192.168.2.10`

### **Key Points: Why Both MAC and IP Addresses Are Needed**

1. **IP addresses** are used for routing data between different networks. They allow routers to forward packets to the correct network.
   
2. **MAC addresses** are used within a **local network** (such as Switch 1 and Switch 2) to ensure the data reaches the correct device on the same network segment.

3. The **router** uses the **IP address** to route packets between different networks and uses **MAC addresses** to deliver the packet within the local network segment.

- **IP Layer (Layer 3)**: Routes the packet based on the IP address.
- **MAC Layer (Layer 2)**: Ensures delivery within the local network using MAC addresses.

### **Conclusion**

--- 
Got it! Let's refine the example based on your clarification, where **Switch 1** connects to **Router 1**, which then connects to **Router 2**, and finally, **Router 2** connects to **Switch 2**. This setup will demonstrate how communication occurs between two computers, one connected to **Switch 1** and the other to **Switch 2**, with two routers in between.

### **Network Topology Setup**

#### **Switch 1**:
- **Computer A** (`IP: 192.168.1.10`, `MAC: AA:AA:AA:AA:AA:AA`)
- **Computer B** (`IP: 192.168.1.11`, `MAC: BB:BB:BB:BB:BB:BB`)

#### **Switch 2**:
- **Computer C** (`IP: 192.168.2.10`, `MAC: CC:CC:CC:CC:CC:CC`)
- **Computer D** (`IP: 192.168.2.11`, `MAC: DD:DD:DD:DD:DD:DD`)

#### **Router 1**:
- **Interface 1 (connected to Switch 1)**: `IP: 192.168.1.1`, `MAC: R1:R1:R1:R1:R1:R1`
- **Interface 2 (connected to Router 2)**: `IP: 10.0.0.1`, `MAC: R2:R2:R2:R2:R2:R2`

#### **Router 2**:
- **Interface 1 (connected to Router 1)**: `IP: 10.0.0.2`, `MAC: R3:R3:R3:R3:R3:R3`
- **Interface 2 (connected to Switch 2)**: `IP: 192.168.2.1`, `MAC: R4:R4:R4:R4:R4:R4`

### **Objective**:
- **Computer A** on **Switch 1** (`192.168.1.10`) wants to communicate with **Computer C** on **Switch 2** (`192.168.2.10`).
  
### **ARP Table Setup**:
We will assume that the ARP tables for the devices involved are populated after ARP requests are resolved, and we are now using them for communication.

### **Step-by-Step Process** (with MAC and IP addresses):

#### **1. Computer A needs to send data to Computer C**:
- **Source**: Computer A (`IP: 192.168.1.10`, `MAC: AA:AA:AA:AA:AA:AA`)
- **Destination**: Computer C (`IP: 192.168.2.10`, `MAC: CC:CC:CC:CC:CC:CC`)

#### **2. Computer A checks if Computer C is on the same subnet**:
- **Computer A** (`192.168.1.10`) and **Computer C** (`192.168.2.10`) are on **different subnets** (`192.168.1.x` and `192.168.2.x`).
- **Computer A** knows that it needs to send the packet to its **default gateway**, which is **Router 1** (`192.168.1.1`).

#### **3. Computer A checks ARP cache for Router 1's MAC address**:
- **Computer A** already knows the **MAC address of Router 1** (`192.168.1.1`, `MAC: R1:R1:R1:R1:R1:R1`).
- No ARP request is needed since the ARP table has this entry.

#### **4. Computer A sends the packet to Router 1**:
- **Computer A** constructs an Ethernet frame to send to **Router 1**:
  - **Source MAC**: `AA:AA:AA:AA:AA:AA` (Computer A)
  - **Destination MAC**: `R1:R1:R1:R1:R1:R1` (Router 1's Interface 1)
  - **Source IP**: `192.168.1.10` (Computer A)
  - **Destination IP**: `192.168.2.10` (Computer C)
  
- **Computer A** sends the packet to **Router 1**.

#### **5. Router 1 receives the packet and forwards it to Router 2**:
- **Router 1** receives the packet and checks the **destination IP** (`192.168.2.10`).
- **Router 1** realizes it needs to forward the packet to **Router 2** over the **10.0.0.x** network.

- **Router 1** rewrites the **Layer 2 (MAC addresses)** to forward the packet to **Router 2**:
  - **Source MAC**: `R2:R2:R2:R2:R2:R2` (Router 1's Interface 2)
  - **Destination MAC**: **(needs Router 2's MAC)**

#### **6. ARP Request from Router 1 to find Router 2's MAC address**:
- **Router 1** sends an **ARP Request** to find the **MAC address** of **Router 2** (`IP: 10.0.0.2`):
  - **Who has IP 10.0.0.2? Tell 10.0.0.1.**
  
#### **7. Router 2 responds with its MAC address**:
- **Router 2** responds with an **ARP Reply**:
  - **I am 10.0.0.2, and my MAC address is R3:R3:R3:R3:R3:R3.**
  
- **Router 1** stores this IP-to-MAC mapping in its ARP cache:
  - **10.0.0.2 -> R3:R3:R3:R3:R3:R3**

#### **8. Router 1 forwards the packet to Router 2**:
- **Router 1** rewrites the Ethernet frame as follows:
  - **Source MAC**: `R2:R2:R2:R2:R2:R2` (Router 1's Interface 2)
  - **Destination MAC**: `R3:R3:R3:R3:R3:R3` (Router 2's Interface 1)
  - **Source IP**: `192.168.1.10` (Computer A)
  - **Destination IP**: `192.168.2.10` (Computer C)

- **Router 1** forwards the packet to **Router 2** over the **10.0.0.x** network.

#### **9. Router 2 receives the packet and forwards it to Computer C**:
- **Router 2** checks the **destination IP** (`192.168.2.10`) and realizes the packet needs to be sent to **Switch 2** to reach **Computer C**.

- **Router 2** rewrites the Ethernet frame to:
  - **Source MAC**: `R4:R4:R4:R4:R4:R4` (Router 2's Interface 2)
  - **Destination MAC**: **(needs Computer C's MAC)**

#### **10. ARP Request from Router 2 to find Computer C's MAC address**:
- **Router 2** sends an **ARP Request** on **Switch 2** to find the MAC address of **Computer C** (`192.168.2.10`):
  - **Who has IP 192.168.2.10? Tell 192.168.2.1.**
  
#### **11. Computer C responds with its MAC address**:
- **Computer C** responds with an **ARP Reply**:
  - **I am 192.168.2.10, and my MAC address is CC:CC:CC:CC:CC:CC.**
  
- **Router 2** stores this IP-to-MAC mapping in its ARP cache:
  - **192.168.2.10 -> CC:CC:CC:CC:CC:CC**

#### **12. Router 2 forwards the packet to Computer C**:
- **Router 2** rewrites the Ethernet frame as follows:
  - **Source MAC**: `R4:R4:R4:R4:R4:R4` (Router 2's Interface 2)
  - **Destination MAC**: `CC:CC:CC:CC:CC:CC` (Computer C)
  - **Source IP**: `192.168.1.10` (Computer A)
  - **Destination IP**: `192.168.2.10` (Computer C)

- **Router 2** forwards the packet to **Computer C** on **Switch 2**.

#### **13. Computer C receives the packet**:
- **Computer C** receives the packet, checks that the **destination IP** matches its own (`192.168.2.10`), and processes the data.

---

### **Summary of MAC and IP Address Usage in This Extended Setup**

1. **Computer A (192.168.1.10) to Router 1 (192.168.1.1)**:
   - **Source MAC**: `AA:AA:AA:AA:AA:AA` (Computer A)
   - **Destination MAC**: `R1:R1:R1:R1:R1:R1` (Router 1's Interface 1)
   - **Source IP**: `192.168.1.10` (Computer A)
   - **Destination IP**: `192.168.2.10` (Computer C)

2. **Router 1 (10.0.0.1) to Router 2 (10.0.0.2)**:
   - **Source MAC**: `R2:R2:R2:R2:R2:R2` (Router 1's Interface 2)
   - **Destination MAC**: `R3:R3:R3:R3:R3:R3` (Router 2's Interface 1)
   - **Source IP**: `192.168.1.10` (Computer A)
   - **Destination IP**: `192.168.2.10` (Computer C)

3. **Router 2 (192.168.2.1) to Computer C (192.168.2.10)**:
   - **Source MAC**: `R4:R4:R4:R4:R4:R4` (Router 2's Interface 2)
   - **Destination MAC**: `CC:CC:CC:CC:CC:CC` (Computer C)
   - **Source IP**: `192.168.1.10` (Computer A)
   - **Destination IP**: `192.168.2.10` (Computer C)

### **Key Points: Why MAC and IP Addresses Are Both Needed**

1. **IP addresses** are used for **routing** between different networks (Layer 3). In this case, **Router 1** and **Router 2** use IP addresses to route the packet from **Switch 1** to **Switch 2**.
  
2. **MAC addresses** are used within each **local network segment** (Layer 2) to ensure that the packet is delivered to the correct device. Each switch or local network uses MAC addresses for communication.

3. **Routers change the MAC addresses** as the packet moves between different network segments, but the **IP addresses remain the same** throughout the journey.

This example highlights how **MAC addresses** are used for local network communication, while **IP addresses** are used for routing packets between networks through **routers**.
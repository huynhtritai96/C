# DHCP
### Application: dynamic assign IP address

When there are **multiple devices** (clients) requesting IP addresses simultaneously or within a short period of time, the **DHCP server** can handle these requests efficiently by keeping track of available IP addresses and responding to each client appropriately. The process works similarly to when a single device requests an IP address, but there are some key details and potential issues to consider, such as **collisions**, **conflicts**, and **DHCP server load**.

### **DHCP with Multiple Requests: Step-by-Step Breakdown**

Let's expand the previous example where **multiple devices** (e.g., multiple laptops, smartphones, or IoT devices) are trying to get an IP address from a DHCP server at the same time.

### **Network Setup**:
- **DHCP Server**: Has a pool of IP addresses to assign (e.g., `192.168.1.100` to `192.168.1.200`).
- **Devices (Clients)**: Let's assume we have **Laptop A**, **Smartphone B**, and **Laptop C** all requesting IP addresses at the same time.

### **Step-by-Step Process with Multiple Requests (DORA Process)**

1. **Multiple Clients Send DHCP Discover**:
   - **Laptop A**, **Smartphone B**, and **Laptop C** are all powered on or join the network, and none of them has an IP address.
   - Each device sends a **DHCP Discover** message. Since the clients don't have an IP address yet, the **source IP** in each request is `0.0.0.0`, and the message is broadcast to the **broadcast IP** `255.255.255.255`.
   - The **DHCP Discover** messages contain the **MAC addresses** of the devices as a unique identifier.
     - **Laptop A**: `MAC A`
     - **Smartphone B**: `MAC B`
     - **Laptop C**: `MAC C`

2. **DHCP Server Receives the Requests**:
   - The **DHCP server** receives the **DHCP Discover** messages from all three devices. Since this is a broadcast, every DHCP-capable server on the network will receive the Discover requests.
   - The server processes each request independently based on the **MAC address** of each device.

2.1   **DHCP Server Sends DHCP Offers**:
   - The DHCP server offers IP addresses to each device by sending a **DHCP Offer** message back to each client. Each offer contains a proposed IP address and other configuration information (subnet mask, gateway, DNS servers, lease time).
     - For **Laptop A** (`MAC A`), the server offers **192.168.1.100**.
     - For **Smartphone B** (`MAC B`), the server offers **192.168.1.101**.
     - For **Laptop C** (`MAC C`), the server offers **192.168.1.102**.
   - The **DHCP Offer** messages are sent directly to the MAC addresses of the respective devices, but since the clients do not yet have IP addresses, they are sent as **broadcasts** (with destination IP `255.255.255.255` and the client's MAC address).

3. **Clients Send DHCP Request**:
   - Each client (Laptop A, Smartphone B, Laptop C) receives the **DHCP Offer** and responds by sending a **DHCP Request** message, requesting to lease the IP address that was offered.
   - The **DHCP Request** is sent as a **broadcast** to inform all DHCP servers on the network (if there are multiple DHCP servers) that the client has selected the offered IP.
     - **Laptop A** sends a **DHCP Request** for **192.168.1.100**.
     - **Smartphone B** sends a **DHCP Request** for **192.168.1.101**.
     - **Laptop C** sends a **DHCP Request** for **192.168.1.102**.

4. **DHCP Server Sends DHCP Acknowledgement (ACK)**:
   - The **DHCP server** receives the **DHCP Request** from each client and responds with a **DHCP Acknowledge** (ACK) message, confirming that the IP address has been leased to the client.
     - **Laptop A** is assigned **192.168.1.100**.
     - **Smartphone B** is assigned **192.168.1.101**.
     - **Laptop C** is assigned **192.168.1.102**.
   - The DHCP ACK contains the lease time, subnet mask, default gateway, and other configuration details (like DNS servers).

4.1 **Clients Receive the Acknowledgement and Start Using the IP Address**:
   - Each client, after receiving the **DHCP ACK**, begins using its assigned IP address to communicate on the network.
   - **Laptop A** can now use **192.168.1.100**.
   - **Smartphone B** can now use **192.168.1.101**.
   - **Laptop C** can now use **192.168.1.102**.


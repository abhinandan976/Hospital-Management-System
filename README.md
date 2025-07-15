# 🏥 Hospital Management 

## 📑 Project Description
This project simulates a **Hospital Management System** written in **C**. It integrates multiple concepts such as **Data Structures, Graph Algorithms (Dijkstra), Heaps, Linear Regression, Sorting, and Resource Management** to model the key components of a hospital, such as:
- Emergency Room management using **Max Heap**
- Resource allocation (Rooms, Beds, ICU, etc.)
- Doctor management via **Linear Search**
- Department routing using **Dijkstra's Algorithm** on a **Graph**
- Predicting patient inflow using **Linear Regression**
- Patient sorting via **Quick Sort**

---

## 🏗️ Project Structure

Hospital-Management-System/
│
├── main.c # Main source code

├── README.md # Project description (this file)

└── requirement.txt


---

## 🚀 Features
### 🏥 Emergency Room (Max Heap)
- Patients are treated based on **urgency priority**.
- Uses a **Max-Heap** to dequeue the most urgent patient first.

### 🏨 Resource Management
- Allocates and deallocates **resources** like rooms, ICU beds, equipment, etc.
- Tracks **available vs allocated** resources.

### 👨‍⚕️ Doctors Management
- Stores doctor information.
- Supports **search by doctor name** via **Linear Search**.

### 🏢 Hospital Departments (Graph)
- Departments connected as nodes in a **Graph**.
- Calculates the **shortest path** between departments using **Dijkstra's Algorithm**.

### 📊 Predicting Patient Inflow (Regression)
- Uses **Linear Regression** to predict patient inflow based on **temperature and humidity**.

### 🧑‍🤝‍🧑 Patient Management (Quick Sort)
- Patient names are sorted alphabetically using **Quick Sort**.

---

## ⚙️ How to Run
### 1️⃣ Compile the code
```bash
gcc main.c -o hospital

./hospital

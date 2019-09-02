---
title: Constructor
parent: R6Connection
layout: default
nav_order: 1
permalink: "/R6Connection/R6Connection"
---

### Return Type: [R6Connection](/R6pp/R6Connection)

### Arguments
* `std::string` email
 * The ubisoft account email
* `std::string` password
 *  The ubisoft account password

### Definition
```cpp
R6Connection(std::string email, std::string password)
```

### Note(s)
WARNING
{: .label .label-red } 
The password is not saved into memory by R6pp, once the constructor returns the argument should be thrown away off of the [stack](https://www.tenouk.com/Bufferoverflowc/Bufferoverflow2.html).
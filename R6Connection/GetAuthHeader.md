---
title: GetAuthHeader
parent: R6Connection
layout: default
nav_order: 3
permalink: "/R6Connection/GetAuthHeader"
---

### Return Type: [AuthenticationHeader ](/R6pp/Types/AuthenticationHeader )

### Function arguments
 - none
 - 
### Definition
```cpp
AuthenticationHeader GetAuthHeader() {return this->_authHeader;}
```

### Note(s)

Under normal circumstances this function should not be needed, an internal instance of the authentication header is set by the [Constructor] (/R6Connection/R6Connection)
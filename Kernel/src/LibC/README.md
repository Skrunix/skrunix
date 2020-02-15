# Freestanding LibC (C11)

## Requirements

- <float.h>
- <iso646.h>
- <limits.h>
- <stdalign.h>
- <stdarg.h>
- <stdbool.h>
- <stddef.h>
- <stdint.h>
- <stdnoreturn.h>

## Template

```C
#pragma once

#if defined(__cplusplus)
extern "C" {
#endif
 
...
 
#if defined(__cplusplus)
} /* extern "C" */
#endif
```

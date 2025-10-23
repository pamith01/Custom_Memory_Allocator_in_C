Custom Memory Allocator in C (Low-Level Systems Project)
• Designed a custom memory allocator with a 1GB static heap, optimized for word-aligned allocations.
• Developed core allocation logic (alloc, destroy, findblock, mkalloc) with bitfield-based headers for efficient
memory tracking.
• Implemented block splitting, zeroing of freed memory, and recursive block search for optimal allocation.

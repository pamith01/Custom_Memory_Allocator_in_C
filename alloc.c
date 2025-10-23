/* alloc.c */
#include "alloc.h"

extern heap *memspace;

public bool destroy(void *addr) {
    header *p;
    int16 n;
    void *mem;
    word w;

    mem = addr - 4;
    p = $h mem;
    w = (p->w == ZeroWords) ? 0 : p->w;

    ((!w) || (!(p->alloced))) ? ({
        reterr(Err2xFree);
    })
    : (void)0;
    
    n = ((p->w-1) * 4);
    zero($1 addr, n);
    p->alloced = false;

    return true;
}

private header *findblock_(header *hdr, word allocation, word n) {
    bool ok;
    void *mem;
    header *hdr_;
    word n_, w;

    if ((n+allocation) > (Maxwords-2))
        reterr(ErrNoMem);
    
    w = (hdr->w == ZeroWords) ? 0 : hdr->w;
    ok = (!hdr->w) ? true :
        (!(hdr->alloced) && (w >= allocation)) ? true :
        false;
    
    if (ok)
        return hdr;
    else {
        mem = $v (($1 hdr) + (w*4) +4);
        hdr_ = $h mem;
        n_ = n + w;

        return findblock_(hdr_, allocation, n_);
    }

    reterr(ErrUnknown);
}

private void *mkalloc(word words, header *hdr) {
    void *ret, *bytesin, *mem;
    word wordsin, diff;
    header *hdr_;

    bytesin = ($v (($v hdr) - memspace));
    wordsin = (((word)bytesin)/4)+1;
    if (words > (Maxwords-wordsin))
        reterr(ErrNoMem);

    if (hdr->w > words) {
        diff = hdr->w - words;

        mem = $v (($1 hdr) + (words*4) + 4);
        hdr_ = $h mem;
        diff--;
        hdr_->w = (!diff) ? ZeroWords : diff;
        hdr_->alloced = false;
    }

    hdr->w = words;
    hdr->alloced = true;
    ret = ($v hdr)+4;

    return ret;
}

public void *alloc(int32 bytes) {
    word words;
    header *hdr;
    void *mem;

    words = (!(bytes % 4)) ?
            bytes/4 :
        (bytes/4) + 1;
    
    hdr = findblock(words);
    if (!hdr)
        return $v 0;

    if (words > Maxwords)
        reterr(ErrNoMem);
    
    mem = mkalloc(words, hdr);
    if (!mem)
        return $v 0;
    
    return mem;
}

private void show_(header *hdr) {
    header *p;
    void *mem;
    int32 n;
    word w;

    for (n=1, p=hdr, w=(p->w == ZeroWords) ? 0 : p->w; p->w;
        mem=$v p + ((w+1)*4), p=mem, w=(p->w == ZeroWords) ? 0 : p->w, n++)
        {
            if (!w) {
                printf("Empty header at 0x%.08x, moving on\n", $i p);
                continue;
            }
            printf("0x%.08x Alloc %d = %d %s words\n", $i ($1 p+4),
                 n, w, (p->alloced) ? "alloced" : "free");
        }
    
    return;
}

int main(int argc, char *argv[]) {
    int8 *p;
    int8 *p2;
    int8 *p3;
    int8 *p4;

    p = alloc(7);
    p2 = alloc(2000);
    p3 = alloc(10);
    destroy(p2);
    p4 = alloc(1996);
    show();


    return 0;
}
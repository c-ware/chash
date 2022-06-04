/*
 * A basic stress test for chash. This will add 100 strings into
 * the hashtable, and verify that they all exist inside of it.
*/

#include "common.h"

int main(void) {
    int index = 0;
    int value = -1;
    char *strings[100] = {
        "mjh", "exc", "yqq", "wjr", "hal", "ttc", "vkr", "ush", "nnl", "vrd",
        "iqw", "nlp", "maz", "xbn", "ipi", "mud", "pbu", "lgv", "qmd", "hjh",
        "vsv", "kyp", "sft", "gxv", "xsw", "mzu", "bfb", "wpv", "nan", "ezz",
        "rrt", "mnp", "ies", "vpk", "xuq", "peu", "hjj", "hii", "ibc", "tvi",
        "cld", "uqv", "nff", "rrm", "jbw", "cjn", "thw", "rmn", "tlk", "bmb",
        "pdx", "pax", "ksw", "ufc", "lgm", "fwt", "ngu", "unc", "teh", "uda",
        "yrj", "gjp", "wom", "jqi", "vld", "rxs", "lmn", "aff", "ogh", "cle",
        "yvi", "ftl", "ypb", "qcg", "lpy", "erc", "frr", "whm", "atq", "jti",
        "byc", "ybl", "rkx", "sdm", "qnf", "iuw", "lri", "fui", "usg", "xjh",
        "ezq", "beq", "kzu", "ezj", "bhj", "dgv", "wez", "pjr", "kvl", "egh",
    };

    struct StringHashtable *stress_table = chash_init(stress_table,
                                                      STRING_TABLE);

    /* Add each string */
    for(index = 0; index < 100; index++) {
        chash_assign(stress_table, strings[index], index, STRING_TABLE);
    }

    /* Correct length? */
    assert(stress_table->length == 100);

    /* Verify each string is inside the hashtable, and they have the
     * correct value */
    for(index = 0; index < 100; index++) {
        value = chash_lookup(stress_table, strings[index], value, STRING_TABLE);
        assert(value == index);
    }

    chash_free(stress_table, STRING_TABLE);

    return EXIT_SUCCESS;
}

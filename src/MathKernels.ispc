
export void match_all_ispc(uniform const unsigned int8 a[], uniform int n_size_a,
                    uniform const unsigned int8 b[], uniform int n_size_b,
                    uniform int n_dim, uniform int index_ab[], uniform int distance_ab[]) {
    for (uniform int i = 0; i < n_size_a; i++) {
        for (uniform int j = 0; j < n_size_b; j++) {
            int8 d_ab_v = 0;
            foreach (k = 0 ... n_dim) {
                d_ab_v += a[i * n_dim + k] ^ b[j * n_dim + k];
            }
            uniform int d_ab = reduce_add(d_ab_v);
            uniform int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}
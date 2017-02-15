// dimension is a type that depends on integers D, T, M
// these represent Distance units, Time units, Mass units
template<int D, int T, int M>
struct dimension {
    // it contains a value
    float val;
    // it can be initialised using a float value
    dimension(float x):val(x){};

    // you could multiply with another dimension of same units
    dimension<D,T,M> operator+(const dimension<D,T,M> another) const {
        return dimension<D,T,M> (val+another.val);
    }

    // you could compare with another dimension of same units
    bool operator<(const dimension<D,T,M> another) const {
        return (val<another.val);
    }

    // you could multiply with a scalar
    dimension<D,T,M> operator*(const float scalar) const {
        return dimension<D,T,M> (val*scalar);
    }
};

// If you want to multiply two dimensions, you will get a third dimension
// of units added up
template<int D, int T, int M, int D2, int T2, int M2>
dimension<D+D2,T+T2,M+M2> operator*( const dimension<D,T,M> a,
                                    const dimension<D2,T2,M2> b) {
        return dimension<D+D2,T+T2,M+M2> (a.val*b.val);
    }

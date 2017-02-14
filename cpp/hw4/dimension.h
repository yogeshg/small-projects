template<int D, int T, int M>
struct dimension {
    float val;
    dimension(float x):val(x){};
    dimension<D,T,M> operator*(const float scalar) const {
        return dimension<D,T,M> (val*scalar);
    }
    dimension<D,T,M> operator+(const dimension<D,T,M> another) const {
        return dimension<D,T,M> (val+another.val);
    }
    bool operator<(const dimension<D,T,M> another) const {
        return (val<another.val);
    }
};

template<int D, int T, int M, int D2, int T2, int M2>
dimension<D+D2,T+T2,M+M2> operator*(const dimension<D,T,M> a, const dimension<D2,T2,M2> b) {
        dimension<D+D2,T+T2,M+M2> o(a.val*b.val);
        return o;
    }


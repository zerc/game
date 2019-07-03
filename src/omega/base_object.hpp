class BaseObject {
    public:
        std::string name;

        virtual bool intersects(const Vector& origin, const Vector& dest) =0;
};

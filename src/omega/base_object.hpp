class BaseObject {
    public:
        std::string name;
        std::shared_ptr<Material> material;

        virtual float intersects(const Vector& origin, const Vector& dest, bool edges) =0;
};

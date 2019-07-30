class BaseObject {
    public:
        std::string name;
        std::shared_ptr<Material> material;

        virtual bool intersects(const Vector& origin, const Vector& dest) =0;
};

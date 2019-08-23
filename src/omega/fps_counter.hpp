class FPSCounter {
    private:
        int prev_seconds = 0;
        std::shared_ptr<WindowInterface> window;

    public:
        FPSCounter(const std::shared_ptr<WindowInterface> w) : window(w) {};

        int time() {
            return std::time(nullptr);
        }

        bool second_passed() {
            int t = time();
            return (t % 2 == 0 && t != prev_seconds);
        }

        void display() {
            if (second_passed()) {
                std::cout << "FPS: " << window->get_frames_count() << std::endl;
                window->reset_frames_count();
                prev_seconds = time();
            }
        }
};

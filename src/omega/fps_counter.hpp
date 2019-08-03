class FPSCounter {
    private:
        int prev_seconds = 0;
        std::shared_ptr<WindowInterface> window;

    public:
        FPSCounter(const std::shared_ptr<WindowInterface> w) : window(w) {};

        void display() {
           int t = std::time(nullptr);
            if (t % 2 == 0 && t != prev_seconds) {
                std::cout << "FPS: " << window->get_frames_count() << std::endl;
                window->reset_frames_count();
                prev_seconds = t;
            }
        }
};

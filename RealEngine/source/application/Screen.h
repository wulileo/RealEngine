#ifndef REALENGINE_SCREEN_H
#define REALENGINE_SCREEN_H

class Screen {
public:
    static int get_width() { return width; }

    static int get_height() { return height; }

    static float get_ratio() { return ratio; }

    static void set_width(int w) {
        width = w;
        calculate_ratio();
    }

    static void set_height(int h) {
        height = h;
        calculate_ratio();
    }

    static void set_width_height(int w, int h) {
        width = w;
        height = h;
        calculate_ratio();
    }

private:
    static void calculate_ratio() { ratio = (float) width / (float) height; }

private:
    static int width;
    static int height;
    static float ratio;
};

#endif //REALENGINE_SCREEN_H

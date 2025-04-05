#include "PathFinder.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

PathFinder::PathFinder(const Image<Pixel> &img)
{
    load(img);
} // Constructor delegates to load() function

void PathFinder::load(const Image<Pixel> &img)
{
    // TODO
}

PathFinder::~PathFinder()
{
    clear();
} // Destructor delegates to clear() function

void PathFinder::checkImage(const Image<Pixel> &img)
{
    // TODO
}

void PathFinder::findPath(std::string strategy)
{
    // TODO, strategy is default at "NSWE"
    // Must use Queue ADT to implement BFS algorithm
}

// BONUS: Visualization, should use almost identical codes as above, with some addtions to write to GIF file
void PathFinder::findPathWithVisualization(const std::string &outfile, int frame_duration, int frame_gap, std::string strategy)
{
    // frame_duration and frame_gap should stay the same throughout the function

    // Initialize GIF writer
    int cell_size = 1; // Each cell is 1x1 pixels, you can change this to a larger size if needed
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;

    int frame_counter = 0; // each movement is a frame and you can define how frequently you want to write the frame

    GifWriter gif; // a gif object has been declared and is pending for writing
    if (!GifBegin(&gif, (outfile + ".gif").c_str(), gif_width, gif_height, frame_duration, 8, true))
    {
        throw std::runtime_error("Failed to create GIF file.");
    }

    // TODO, strategy is default at "NSWE"
    // Must use Queue ADT to implement BFS algorithm with visualization

    // Must use `` addFrameToGif(gif, frame_duration) `` at certain time to write the frame to the gif
    // Before each of your function exit (e.g., return or throw), you have to conclude the gif object
    // by `` GifEnd(&gif); ``

    // It's also expected to have
    // ``writeToFile(image, outfile + "_final_visual.png")`` at the end of pathfinding
    GifEnd(&gif);
}

// Helper function
void PathFinder::addFrameToGif(GifWriter &gif, int frame_duration)
{
    // Each coordinate is 1x1 pixels, you can change this to a larger size if needed
    int cell_size = 1;
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;
    // 4 is the number of channels (RGBA)
    std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

    // Convert the image to RGB format for the GIF
    for (int r = 0; r < image.height(); ++r)
    {
        for (int c = 0; c < image.width(); ++c)
        {
            Pixel color;
            if (image(r, c) == WHITE)
            {
                color = {255, 255, 255};
            }
            else if (image(r, c) == BLACK)
            {
                color = {0, 0, 0};
            }
            else if (image(r, c) == RED)
            {
                color = {255, 0, 0};
            }
            else if (image(r, c) == GREEN)
            {
                color = {0, 255, 0};
            }
            else if (image(r, c) == BLUE)
            {
                color = {0, 0, 255};
            }
            else if (image(r, c) == YELLOW)
            {
                color = {255, 255, 0};
            }
            else
            {
                color = {0, 0, 0};
            }

            // Fill the cell with the color
            for (int i = 0; i < cell_size; ++i)
            {
                for (int j = 0; j < cell_size; ++j)
                {
                    int pixel_row = r * cell_size + i;
                    int pixel_col = c * cell_size + j;
                    int index = (pixel_row * gif_width + pixel_col) * 4;
                    rgb_data[index + 0] = color.red;
                    rgb_data[index + 1] = color.green;
                    rgb_data[index + 2] = color.blue;
                    rgb_data[index + 3] = 255; // Alpha channel
                }
            }
        }
    }
    // Write the frame to the GIF
    GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
} // Finished

void PathFinder::writeSolutionToFile(const std::string &filename)
{
    writeToFile(image, filename);
} // delegate to writeToFile function in lib/image.h

Coord PathFinder::getStart()
{
    // TODO
    return Coord(); // placeholder
}

Coord PathFinder::getEnd()
{
    // TODO
    return Coord(); // placeholder
}

void PathFinder::clear()
{
    // TODO
}

// Nonmember functions
bool compareImagesExit(std::string img1_str, std::string img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            // Check if the pixels are different and one of them is GREEN
            if (img1(r, c) != img2(r, c) && (img1(r, c) == GREEN || img2(r, c) == GREEN))
            {
                return false;
            }
        }
    }
    return true;
} // Finished

bool compareImages(std::string img1_str, std::string img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            if (img1(r, c) != img2(r, c))
            {
                return false;
            }
        }
    }
    return true;
} // Finished
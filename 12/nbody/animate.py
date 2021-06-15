#!/usr/bin/python3

import json
import os
import subprocess

import matplotlib.pyplot as plt


def scatterplot(n, xs, ys, zs):
    filename = f"images/figure{n:05d}.png"

    fig = plt.figure()
    plt.tight_layout()

    ax = fig.add_subplot(projection="3d")
    ax.scatter(xs, ys, zs, marker="o")
    
    ax.set_xlim(-30, 30)
    ax.set_ylim(-30, 30)
    ax.set_zlim(-30, 30)

    plt.savefig(filename)
    plt.close()

    return filename


def plots(series):
    filenames = []

    for n, data in enumerate(series):
        xs = []
        ys = []
        zs = []

        for point in data:
            xs.append(point[0])
            ys.append(point[1])
            zs.append(point[2])

        fn = scatterplot(n, xs, ys, zs)
        filenames.append(fn)

    return filenames


def main():
    with open("output.json") as file:
        data = file.read()

    series = json.loads(data)

    os.makedirs("./images", exist_ok=True)

    fns = plots(series)

    # render GIF
    # requires ImageMagick
    ret = subprocess.run(["convert", "-delay", "1", "-loop", "0"] + fns + ["animation.gif"])
    ret.check_returncode()

    # render H264 video
    # requires FFMpeg with x264 support
    ret = subprocess.run([
        "ffmpeg", "-hide_banner",
        "-loglevel", "error",
        "-r", "25", "-f", "image2",
        "-i", "images/figure%05d.png",
        "-vcodec", "libx264",
        "-crf", "25",
        "-pix_fmt", "yuv420p",
        "-y", "animation.mp4",
    ])
    ret.check_returncode()

    for fn in fns:
        os.remove(fn)

    return 0


if __name__ == "__main__":
    exit(main())


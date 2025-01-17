# AVFormatContext，AVInputFormat，AVOutputFormat有什么关系
**用于封装和解封装的核心数据结构是 AVFormatContext ，它包含所有关于正在读取或写入的文件的信息。**

要创建一个 AVFormatContext ，通常使用 avformat_alloc_context() 函数。

在FFmpeg中，`AVFormatContext`、`AVInputFormat` 和 `AVOutputFormat` 之间的关系如下：

1. **AVFormatContext**:
   - `AVFormatContext` 是FFmpeg库中用来描述多媒体文件或流的容器。它包含了文件格式、流信息、编解码器信息等，实际上就是FFmpeg中用于存储输入或输出流相关信息的结构体。
   - 它的作用是管理输入/输出流的格式，通常通过该上下文来打开文件、读取数据或写入数据。

2. **AVInputFormat**:
   - `AVInputFormat` 是用于输入格式的结构体，描述了FFmpeg支持的各种输入格式（例如，MP4、AVI、FLV等）。它负责告诉FFmpeg如何解析输入流的数据。
   - 例如，`AVInputFormat` 负责将文件中的多媒体数据转换成`AVPacket`形式提供给用户。它的作用是实现输入流的解封装（demuxing）过程。

3. **AVOutputFormat**:
   - `AVOutputFormat` 是用于输出格式的结构体，描述了FFmpeg支持的各种输出格式（如：MP4、FLV、AVI等）。它负责将用户提供的音视频数据封装成特定格式进行输出。
   - 它的作用是实现封装（muxing）过程，将音视频数据写入输出文件。

### 关系：
- `AVFormatContext` 是一个包含输入/输出格式信息的容器，具体使用哪个输入或输出格式取决于 `AVInputFormat` 或 `AVOutputFormat`。
- 对于输入流，`AVFormatContext` 会使用某种 `AVInputFormat` 来解析文件或流。
- 对于输出流，`AVFormatContext` 会使用某种 `AVOutputFormat` 来封装音视频数据。

简单来说，`AVFormatContext` 是操作音视频流的核心结构，它通过 `AVInputFormat` 来解析输入流，通过 `AVOutputFormat` 来封装输出流。

### 举个例子：
- 在打开一个媒体文件时，FFmpeg会选择一个合适的 `AVInputFormat`，比如 `mp4` 输入格式。
- 然后，`AVFormatContext` 会加载该输入格式的相关信息，使用 `AVInputFormat` 的函数来解析文件。
- 在输出时，FFmpeg会选择一个合适的 `AVOutputFormat`（比如 `mp4` 输出格式），并通过 `AVFormatContext` 使用该格式来封装音视频流。

希望这个解释清晰！

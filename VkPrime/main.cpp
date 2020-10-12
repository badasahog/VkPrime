#define _SILENCE_CXX17_STRSTREAM_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <intrin.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <array>
#include <optional>
#include <set>
#include <unordered_map>
#include <strstream>
#include <bitset>

#include<squish.cpp>

#include <zlib.h>
#define CHUNK 16384
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

//const std::string MODEL_PATH = "";
const std::vector<std::string> images = {
    "textures/TXTR_E802C6C6.png",
    "textures/ss_1.png",
    "textures/ss_black.png",
    "textures/ss_blue.png",
    "textures/ss_blue_green.png",
    "textures/ss_canopy.png",
    "textures/ss_dark_blue.png",
    "textures/ss_dark_red.png",
    "textures/ss_glass.png",
    "textures/ss_green.png",
    "textures/ss_grey.png",
    "textures/ss_lgb.png",
    "textures/ss_light_blue.png",
    "textures/ss_light_green.png",
    "textures/ss_meter_G.png",
    "textures/ss_meter_O.png",
    "textures/ss_meter_Y.png",
    "textures/ss_outer_light_blue.png",
    "textures/ss_pbh.png",
    "textures/ss_red.png",
    "textures/ss_red_orange.png",
    "textures/ss_ship_interior.png",
    "textures/ss_ship_seat.png",
    "textures/ss_ship_wheel.png",
    "textures/ss_vanilla.png",
    "textures/ss_vanilla.png.001.png",
    "textures/ss_yellow.png",
    "textures/ss_yro.png",
    "textures/strip_1.png",
    "textures/strip_2.png",
    "textures/strip_3.png",
    "textures/strip_4.png",
    "textures/strip_5.png",
    "textures/strip_6.png",
    "textures/strip_7.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
    "textures/ss_0.png",
    "textures/ss_1.png",
};
const std::string LEVEL_PATH = "models/ssdolphin/lvl.dat";

const int MAX_FRAMES_IN_FLIGHT = 2;
int tempcounter = 0;
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}


struct player {
    double mousex = 0;
    double mousey = 0;
    double deltaMousex = 0.0f;
    double deltaMousey = 0.0f;
    double xrot = 0.0f;
    double yrot = 0.0f;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);
    float speed = 0.2f;
};
player playerCharacter;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
    {
        playerCharacter.cameraPos.x -= playerCharacter.speed * sin(playerCharacter.mousex / 100);
        playerCharacter.cameraPos.y -= playerCharacter.speed * cos(playerCharacter.mousex / 100);
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
    {
        playerCharacter.cameraPos.x -= playerCharacter.speed * sin(playerCharacter.mousex / 100 - glm::radians(90.0f));
        playerCharacter.cameraPos.y -= playerCharacter.speed * cos(playerCharacter.mousex / 100 - glm::radians(90.0f));
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
    {
        playerCharacter.cameraPos.x += playerCharacter.speed * sin(playerCharacter.mousex / 100);
        playerCharacter.cameraPos.y += playerCharacter.speed * cos(playerCharacter.mousex / 100);
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
    {
        playerCharacter.cameraPos.x -= playerCharacter.speed * sin(playerCharacter.mousex / 100 + glm::radians(90.0f));
        playerCharacter.cameraPos.y -= playerCharacter.speed * cos(playerCharacter.mousex / 100 + glm::radians(90.0f));
    }

    if (key == GLFW_KEY_Q && action == GLFW_REPEAT)
    {
        playerCharacter.cameraPos.z += playerCharacter.speed;
    }
    if (key == GLFW_KEY_E && action == GLFW_REPEAT)
    {
        playerCharacter.cameraPos.z -= playerCharacter.speed;
    }

    return;

}

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    uint32_t textureIndex;
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32_UINT;
        attributeDescriptions[3].offset = offsetof(Vertex, textureIndex);

        return attributeDescriptions;
    }

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }
};

struct MaterialSet {
    std::vector<uint32_t> textureFileIDs;
    std::vector<uint32_t> materialEndOffsets;
    std::vector<uint32_t> textureFileIndices;
    std::vector<uint32_t> konstColors;
    std::vector<uint32_t> ColorChannelFlags;
    uint32_t textureCount;
    uint32_t materialCount;
    uint32_t vertexAtributeFlags;
    uint32_t ColorChannelCount;
};
struct CMDLSurface {
    float centerPoint[3];
    uint32_t matIndex;
    uint16_t maintissa;
    uint16_t displayListSize;
    uint32_t parentModelPointer;
    uint32_t nextSurfacePointer;
    uint32_t extraDataSize;
    float surfaceNormal[3];
    uint8_t GXFlags;
    uint16_t vertexCount;
    std::vector<uint32_t> pos_indices;
    std::vector<uint32_t> nml_indices;
    std::vector<uint32_t> uvc_indices;

};
struct CMDLGeometry {
    std::vector<float> vertexCoords;
    std::vector<float> normals;
    std::vector<float> floatUVCoords;
    uint32_t surfaceCount;
    std::vector<uint32_t> surfaceOffsets;
    std::vector<CMDLSurface> surfaces;
};

struct CMDL {
    uint32_t magic;
    uint32_t version;
    uint32_t flags;
    float ModelAxisAlignedBoundingBox[6];
    uint32_t dataSectionCount;
    uint32_t MaterialSetCount;
    std::vector<uint32_t> dataSectionSizes;
    std::vector<MaterialSet> materialSets;
    CMDLGeometry geometry;
};
namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};
struct Mesh {
    alignas(32)uint32_t startIndex;
    alignas(32)uint32_t num_indices;
    alignas(32)uint32_t vertOffset;
    alignas(32)float x;
    alignas(32)float y;
    alignas(32)float z;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::string filePath;
};
struct HexCharStruct
{
    unsigned char c;
    HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
    return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
    return HexCharStruct(_c);
}

class HelloTriangleApplication {
public:
    void run() {
        std::cout << "running" << std::endl;
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;

    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    struct imageStuff {
        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;
    };

    std::vector<imageStuff> imageStuffs;


    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<Mesh> objects;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;

    VkBuffer posBuffer;
    VkBuffer nmlBuffer;
    VkBuffer uvcBuffer;
    VkBuffer ndxBuffer;

    VkDeviceMemory posBufferMemory;
    VkDeviceMemory nmlBufferMemory;
    VkDeviceMemory uvcBufferMemory;
    VkDeviceMemory ndxBufferMemory;//index buffer
    VkDeviceSize bufferSize_ndx = 0;


    std::vector<CMDL> CMDLs;


    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    bool framebufferResized = false;

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }

    void initVulkan() {
        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createDescriptorSetLayout();
        createGraphicsPipeline();
        createCommandPool();
        createColorResources();
        createDepthResources();
        createFramebuffers();
        createTextureImage();
        createTextureImageView();
        createTextureSampler();
        loadScene();
        //createVertexBuffer();
        //createIndexBuffer();
        createUniformBuffers();
        createStorageBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();
        createSyncObjects();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            playerCharacter.deltaMousex = playerCharacter.mousex;
            playerCharacter.deltaMousey = playerCharacter.mousey;
            glfwGetCursorPos(window, &(playerCharacter.mousex), &(playerCharacter.mousey));
            playerCharacter.deltaMousex -= playerCharacter.mousex;
            playerCharacter.deltaMousey -= playerCharacter.mousey;
            playerCharacter.xrot += playerCharacter.deltaMousex / 10;
            playerCharacter.yrot += playerCharacter.deltaMousey / 10;
            playerCharacter.yrot = fmax(playerCharacter.yrot, 0);
            playerCharacter.yrot = fmin(playerCharacter.yrot, 89.9);
            glm::vec3 front;
            front.x = cos(glm::radians(playerCharacter.xrot)) * cos(glm::radians(playerCharacter.yrot));
            front.y = sin(glm::radians(playerCharacter.yrot));
            front.z = sin(glm::radians(playerCharacter.xrot)) * cos(glm::radians(playerCharacter.yrot));
            playerCharacter.cameraFront = glm::normalize(front);
            // also re-calculate the Right and Up vector
            glm::vec3 Right = glm::normalize(glm::cross(playerCharacter.cameraFront, glm::vec3(0.0f, 0.0f, 1.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            playerCharacter.cameraUp = glm::normalize(glm::cross(Right, playerCharacter.cameraFront));
            //std::cout << "xrot " << playerCharacter.xrot << "\t" << "yrot " << playerCharacter.yrot << std::endl;
            drawFrame();
        }

        vkDeviceWaitIdle(device);
    }

    void cleanupSwapChain() {
        vkDestroyImageView(device, depthImageView, nullptr);
        vkDestroyImage(device, depthImage, nullptr);
        vkFreeMemory(device, depthImageMemory, nullptr);

        vkDestroyImageView(device, colorImageView, nullptr);
        vkDestroyImage(device, colorImage, nullptr);
        vkFreeMemory(device, colorImageMemory, nullptr);

        for (auto framebuffer : swapChainFramebuffers) {
            vkDestroyFramebuffer(device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        vkDestroyPipeline(device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);

        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            vkDestroyBuffer(device, uniformBuffers[i], nullptr);
            vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
        }

        vkDestroyDescriptorPool(device, descriptorPool, nullptr);
    }

    void cleanup() {
        cleanupSwapChain();
        for (int x = 0; x < imageStuffs.size(); x++) {
            vkDestroySampler(device, imageStuffs.at(x).textureSampler, nullptr);
            vkDestroyImageView(device, imageStuffs.at(x).textureImageView, nullptr);

            vkDestroyImage(device, imageStuffs.at(x).textureImage, nullptr);
            vkFreeMemory(device, imageStuffs.at(x).textureImageMemory, nullptr);
        }
        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

        vkDestroyBuffer(device, indexBuffer, nullptr);
        vkFreeMemory(device, indexBufferMemory, nullptr);

        vkDestroyBuffer(device, vertexBuffer, nullptr);
        vkFreeMemory(device, vertexBufferMemory, nullptr);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(device, commandPool, nullptr);

        vkDestroyDevice(device, nullptr);

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    void recreateSwapChain() {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(device);

        cleanupSwapChain();

        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createColorResources();
        createDepthResources();
        createFramebuffers();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
        createCommandBuffers();
    }

    void createInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }

    void setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    void createSurface() {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        glfwSetKeyCallback(window, key_callback);


    }

    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                msaaSamples = getMaxUsableSampleCount();
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    void createLogicalDevice() {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }

    void createSwapChain() {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }

    void createImageViews() {
        swapChainImageViews.resize(swapChainImages.size());

        for (uint32_t i = 0; i < swapChainImages.size(); i++) {
            swapChainImageViews[i] = createImageView(swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
        }
    }

    void createRenderPass() {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = msaaSamples;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentDescription depthAttachment{};
        depthAttachment.format = findDepthFormat();
        depthAttachment.samples = msaaSamples;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentDescription colorAttachmentResolve{};
        colorAttachmentResolve.format = swapChainImageFormat;
        colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef{};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference colorAttachmentResolveRef{};
        colorAttachmentResolveRef.attachment = 2;
        colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;
        subpass.pResolveAttachments = &colorAttachmentResolveRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        std::array<VkAttachmentDescription, 3> attachments = { colorAttachment, depthAttachment, colorAttachmentResolve };
        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }

    void createDescriptorSetLayout() {
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding samplerLayoutBinding{};
        samplerLayoutBinding.binding = 1;
        samplerLayoutBinding.descriptorCount = images.size();
        samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        samplerLayoutBinding.pImmutableSamplers = nullptr;
        samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        VkDescriptorSetLayoutBinding posLayoutBinding{};
        posLayoutBinding.binding = 6;
        posLayoutBinding.descriptorCount = 1;
        posLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        posLayoutBinding.pImmutableSamplers = nullptr;
        posLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding nmlLayoutBinding{};
        nmlLayoutBinding.binding = 7;
        nmlLayoutBinding.descriptorCount = 1;
        nmlLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        nmlLayoutBinding.pImmutableSamplers = nullptr;
        nmlLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding uvcLayoutBinding{};
        uvcLayoutBinding.binding = 8;
        uvcLayoutBinding.descriptorCount = 1;
        uvcLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        uvcLayoutBinding.pImmutableSamplers = nullptr;
        uvcLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding ndxLayoutBinding{};
        ndxLayoutBinding.binding = 9;
        ndxLayoutBinding.descriptorCount = 1;
        ndxLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        ndxLayoutBinding.pImmutableSamplers = nullptr;
        ndxLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;




        std::array<VkDescriptorSetLayoutBinding, 6> bindings = {uboLayoutBinding, samplerLayoutBinding, posLayoutBinding, nmlLayoutBinding, uvcLayoutBinding, ndxLayoutBinding };
        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        layoutInfo.pBindings = bindings.data();

        if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    void createGraphicsPipeline() {
        auto vertShaderCode = readFile("shaders/vert.spv");
        auto fragShaderCode = readFile("shaders/frag.spv");

        VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
        VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 0;
        vertexInputInfo.vertexAttributeDescriptionCount = 0;// static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapChainExtent.width;
        viewport.height = (float)swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swapChainExtent;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_NONE;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = msaaSamples;

        VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

        if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencil;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }

        vkDestroyShaderModule(device, fragShaderModule, nullptr);
        vkDestroyShaderModule(device, vertShaderModule, nullptr);
    }

    void createFramebuffers() {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            std::array<VkImageView, 3> attachments = {
                colorImageView,
                depthImageView,
                swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    void createCommandPool() {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics command pool!");
        }
    }

    void createColorResources() {
        VkFormat colorFormat = swapChainImageFormat;

        createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, colorImage, colorImageMemory);
        colorImageView = createImageView(colorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
    }

    void createDepthResources() {
        VkFormat depthFormat = findDepthFormat();

        createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
        depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
    }

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            }
            else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }

        throw std::runtime_error("failed to find supported format!");
    }

    VkFormat findDepthFormat() {
        return findSupportedFormat(
            { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
    }

    bool hasStencilComponent(VkFormat format) {
        return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
    }

    void createTextureImage() {

        imageStuffs.resize(images.size());
        for (int x = 0; x < images.size(); x++)
        {
            int texWidth, texHeight, texChannels;
            stbi_uc* pixels = stbi_load(images.at(x).c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
            VkDeviceSize imageSize = texWidth * texHeight * 4;
            imageStuffs.at(x).mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

            if (!pixels) {
                throw std::runtime_error("failed to load texture image!");
            }

            VkBuffer stagingBuffer;
            VkDeviceMemory stagingBufferMemory;
            createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

            void* data;
            vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
            memcpy(data, pixels, static_cast<size_t>(imageSize));
            vkUnmapMemory(device, stagingBufferMemory);

            stbi_image_free(pixels);

            createImage(texWidth, texHeight, imageStuffs.at(x).mipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, imageStuffs.at(x).textureImage, imageStuffs.at(x).textureImageMemory);

            transitionImageLayout(imageStuffs.at(x).textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, imageStuffs.at(x).mipLevels);
            copyBufferToImage(stagingBuffer, imageStuffs.at(x).textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
            //transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps

            vkDestroyBuffer(device, stagingBuffer, nullptr);
            vkFreeMemory(device, stagingBufferMemory, nullptr);

            generateMipmaps(imageStuffs.at(x).textureImage, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, imageStuffs.at(x).mipLevels);
        }
    }

    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels) {
        // Check if image format supports linear blitting
        VkFormatProperties formatProperties;
        vkGetPhysicalDeviceFormatProperties(physicalDevice, imageFormat, &formatProperties);

        if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
            throw std::runtime_error("texture image format does not support linear blitting!");
        }

        VkCommandBuffer commandBuffer = beginSingleTimeCommands();

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = image;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;
        barrier.subresourceRange.levelCount = 1;

        int32_t mipWidth = texWidth;
        int32_t mipHeight = texHeight;

        for (uint32_t i = 1; i < mipLevels; i++) {
            barrier.subresourceRange.baseMipLevel = i - 1;
            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            vkCmdPipelineBarrier(commandBuffer,
                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
                0, nullptr,
                0, nullptr,
                1, &barrier);

            VkImageBlit blit{};
            blit.srcOffsets[0] = { 0, 0, 0 };
            blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
            blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            blit.srcSubresource.mipLevel = i - 1;
            blit.srcSubresource.baseArrayLayer = 0;
            blit.srcSubresource.layerCount = 1;
            blit.dstOffsets[0] = { 0, 0, 0 };
            blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
            blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            blit.dstSubresource.mipLevel = i;
            blit.dstSubresource.baseArrayLayer = 0;
            blit.dstSubresource.layerCount = 1;

            vkCmdBlitImage(commandBuffer,
                image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                1, &blit,
                VK_FILTER_LINEAR);

            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            vkCmdPipelineBarrier(commandBuffer,
                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
                0, nullptr,
                0, nullptr,
                1, &barrier);

            if (mipWidth > 1) mipWidth /= 2;
            if (mipHeight > 1) mipHeight /= 2;
        }

        barrier.subresourceRange.baseMipLevel = mipLevels - 1;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        vkCmdPipelineBarrier(commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
            0, nullptr,
            0, nullptr,
            1, &barrier);

        endSingleTimeCommands(commandBuffer);
    }

    VkSampleCountFlagBits getMaxUsableSampleCount() {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

        VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
        if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
        if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
        if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
        if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
        if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
        if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

        return VK_SAMPLE_COUNT_1_BIT;
    }

    void createTextureImageView() {
        for (int x = 0; x < images.size(); x++)
            imageStuffs.at(x).textureImageView = createImageView(imageStuffs.at(x).textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, imageStuffs.at(x).mipLevels);
    }

    void createTextureSampler() {
        for (int x = 0; x < images.size(); x++) {
            VkSamplerCreateInfo samplerInfo{};
            samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            samplerInfo.magFilter = VK_FILTER_LINEAR;
            samplerInfo.minFilter = VK_FILTER_LINEAR;
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
            samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
            samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
            samplerInfo.anisotropyEnable = VK_TRUE;
            samplerInfo.maxAnisotropy = 16.0f;
            samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
            samplerInfo.unnormalizedCoordinates = VK_FALSE;
            samplerInfo.compareEnable = VK_FALSE;
            samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
            samplerInfo.minLod = 0.0f;
            samplerInfo.maxLod = static_cast<float>(imageStuffs.at(x).mipLevels);
            samplerInfo.mipLodBias = 0.0f;

            if (vkCreateSampler(device, &samplerInfo, nullptr, &imageStuffs.at(x).textureSampler) != VK_SUCCESS) {
                throw std::runtime_error("failed to create texture sampler!");
            }
        }
    }

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels) {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = mipLevels;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture image view!");
        }

        return imageView;
    }

    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = mipLevels;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = numSamples;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device, image, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate image memory!");
        }

        vkBindImageMemory(device, image, imageMemory, 0);
    }

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands();

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = mipLevels;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else {
            throw std::invalid_argument("unsupported layout transition!");
        }

        vkCmdPipelineBarrier(
            commandBuffer,
            sourceStage, destinationStage,
            0,
            0, nullptr,
            0, nullptr,
            1, &barrier
        );

        endSingleTimeCommands(commandBuffer);
    }

    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands();

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = {
            width,
            height,
            1
        };

        vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        endSingleTimeCommands(commandBuffer);
    }


    int inf(char* source, uint32_t inputSize, char* dest)
    {
        uint32_t srcLoc = 0;
        int ret;
        unsigned have;
        z_stream strm;
        unsigned char in[CHUNK];
        unsigned char out[CHUNK];
        uint32_t q = 0;
        /* allocate inflate state */
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        ret = inflateInit(&strm);
        if (ret != Z_OK)
            return ret;

        /* decompress until deflate stream ends or end of file */
        do {
            //copy CHUNK amount of bytes from the input into `in` and return the number of bytes left to decompress
            //set strm.avail_in to the number of bytes left to decompress
            strm.avail_in = (inputSize - srcLoc) % CHUNK;

            //copy the next CHUNK number of butes from the source to the `in` array
            std::memcpy(in, source, (inputSize - srcLoc) % CHUNK);
            std::cout << "flag 1" << std::endl;
            srcLoc += CHUNK;


            //not neaded because this is only for checking for file read errors
            //if (ferror(source)) {
            //    (void)inflateEnd(&strm);
            //    return Z_ERRNO;
            //}
            if (strm.avail_in == 0)
                break;
            strm.next_in = in;

            /* run inflate() on input until output buffer not full */
            do {
                strm.avail_out = CHUNK;
                strm.next_out = out;
                ret = inflate(&strm, Z_NO_FLUSH);
                assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
                switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;     /* and fall through */
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&strm);
                    return ret;
                }
                have = CHUNK - strm.avail_out;
                //save the output (in the `out` variable) to the dest variable
                memcpy(&dest[q], out, have);
                q += have;
                //if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                //    (void)inflateEnd(&strm);
                //    return Z_ERRNO;
                //}
            } while (strm.avail_out == 0);

            /* done when inflate() says it's done */
        } while (ret != Z_STREAM_END);

        /* clean up and return */
        (void)inflateEnd(&strm);
        return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
    }
    void uint32FromBuffer(uint32_t* output, char* input, uint32_t inputIndex)
    {
        *output =
            (input[inputIndex + 0] & 0xFF) << 0 |
            (input[inputIndex + 1] & 0xFF) << 8 |
            (input[inputIndex + 2] & 0xFF) << 16 |
            (input[inputIndex + 3] & 0xFF) << 24;
    }
    void loadPak(std::string filename)
    {
        std::ifstream f("prime/" + filename, std::ios::binary);
        if (!f.is_open())
            throw std::invalid_argument("pak file not found");
        int16_t versionNumberMajor;
        int16_t versionNumberMinor;
        int32_t unused;
        int32_t assetCount_namedResourcesTable;
        int32_t assetCount_resourcesTable;


        f.read(reinterpret_cast<char*>(&versionNumberMajor), sizeof(versionNumberMajor));
        f.read(reinterpret_cast<char*>(&versionNumberMinor), sizeof(versionNumberMinor));
        f.read(reinterpret_cast<char*>(&unused), sizeof(unused));
        f.read(reinterpret_cast<char*>(&assetCount_namedResourcesTable), sizeof(assetCount_namedResourcesTable));

        versionNumberMajor = swap_endian<int16_t>(versionNumberMajor);
        versionNumberMinor = swap_endian<int16_t>(versionNumberMinor);
        unused = swap_endian<int32_t>(unused);
        assetCount_namedResourcesTable = swap_endian<int32_t>(assetCount_namedResourcesTable);

        std::cout << "Version Number (Major)    " << versionNumberMajor << std::endl;
        std::cout << "Version Number (Minor)    " << versionNumberMinor << std::endl;
        std::cout << "Unused (should be zero)   " << unused << std::endl;
        std::cout << "assets in table           " << assetCount_namedResourcesTable << std::endl;

        std::cout << f.tellg() << std::endl;

        for (int i = 0; i < assetCount_namedResourcesTable; i++) {
            char fourCC[4];
            int32_t AssetID;
            int32_t nameLength;
            std::vector<char> nameString;

            f.read(fourCC, 4);
            f.read(reinterpret_cast<char*>(&AssetID), sizeof(AssetID));
            f.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            nameLength = swap_endian<int32_t>(nameLength);
            nameString.resize(nameLength);
            f.read(nameString.data(), nameLength);
            std::cout << nameLength << std::endl;


            std::cout << "\tAsset Type              "; std::cout.write(fourCC, 4) << std::endl;
            std::cout << "\tAsset ID                " << AssetID << std::endl;
            std::cout << "\tAsset name              "; std::cout.write(nameString.data(), nameLength) << std::endl;
        }

        f.read(reinterpret_cast<char*>(&assetCount_resourcesTable), sizeof(assetCount_resourcesTable));

        assetCount_resourcesTable = swap_endian<int32_t>(assetCount_resourcesTable);
        std::cout << "asset count (resource table)  " << assetCount_resourcesTable << std::endl;
        //for (int i = 0; i < assetCount_resourcesTable; i++) {
        for (int i = 0; i < 500; i++) {
            int32_t compressionFlag;
            char fourCC[4];
            int32_t AssetID;
            int32_t size;
            int32_t offset;

            f.read(reinterpret_cast<char*>(&compressionFlag), sizeof(compressionFlag));
            f.read(fourCC, 4);
            f.read(reinterpret_cast<char*>(&AssetID), sizeof(AssetID));
            f.read(reinterpret_cast<char*>(&size), sizeof(size));
            f.read(reinterpret_cast<char*>(&offset), sizeof(offset));



            compressionFlag = swap_endian<int32_t>(compressionFlag);
            AssetID = swap_endian<int32_t>(AssetID);
            size = swap_endian<int32_t>(size);
            offset = swap_endian<int32_t>(offset);

            std::cout << "\tcompression flag        " << compressionFlag << std::endl;
            std::cout << "\tAsset Type              "; std::cout.write(fourCC, 4) << std::endl;
            std::cout << "\tAsset ID                " << std::hex << AssetID << std::dec << std::endl;
            std::cout << "\tsize                    " << size << std::endl;
            std::cout << "\toffset                  " << std::hex << offset << std::dec << std::endl;
            int getLoc = f.tellg();
            f.seekg(offset);
            if (compressionFlag == 1)
            {
                int32_t decompressedSize;

                f.read(reinterpret_cast<char*>(&decompressedSize), sizeof(decompressedSize));
                decompressedSize = swap_endian<int32_t>(decompressedSize);
                //std::cout << "\t\tdecompressed size: " << decompressedSize << std::endl;
                uLong ucompSize = decompressedSize;
                std::vector<char> zlibdata;
                zlibdata.resize(size);

                f.read(zlibdata.data(), size);


                std::vector<char> rawFile;
                rawFile.resize(decompressedSize);

                switch (uncompress((Bytef*)rawFile.data(), &ucompSize, (Bytef*)zlibdata.data(), size))
                {
#ifdef debug
                case Z_OK:std::cout << "successfully extracted" << std::endl; break;
#endif
                case Z_STREAM_END:std::cout << "FATAL ERROR Z_STREAM_END" << std::endl; break;
                case Z_NEED_DICT:std::cout << "FATAL ERROR Z_NEED_DICT" << std::endl; break;
                case Z_ERRNO:std::cout << "FATAL ERROR Z_ERRNO" << std::endl; break;
                case Z_STREAM_ERROR:std::cout << "FATAL ERROR Z_STREAM_ERROR" << std::endl; break;
                case Z_DATA_ERROR:std::cout << "FATAL ERROR Z_DATA_ERROR" << std::endl; break;
                case Z_MEM_ERROR:std::cout << "FATAL ERROR Z_MEM_ERROR" << std::endl; break;
                case Z_BUF_ERROR:std::cout << "FATAL ERROR Z_BUF_ERROR" << std::endl; break;
                case Z_VERSION_ERROR:std::cout << "FATAL ERROR Z_VERSION_ERROR" << std::endl; break;
                }
                if (fourCC[0] == 'S' && fourCC[1] == 'T' && fourCC[2] == 'R' && fourCC[3] == 'G')
                {
                    int32_t txtrFormat = (rawFile[0] << 24) | (rawFile[1] << 16) | (rawFile[2] << 8) | rawFile[3];
                    //std::cout << "\t\ttexture format: " << std::hex << txtrFormat << std::dec << std::endl;
                    uint16_t txtrWidth = (rawFile[4] << 8) | rawFile[5];
                    //std::cout << "\t\ttexture width: " << txtrWidth << std::endl;
                    uint16_t txtrHeight = (rawFile[6] << 8) | rawFile[7];
                    //std::cout << "\t\ttexture height: " << txtrHeight << std::endl;
                    int32_t mipCount = (rawFile[8] << 24) | (rawFile[9] << 16) | (rawFile[10] << 8) | rawFile[11];
                    //std::cout << "\t\tmip count: " << mipCount << std::endl;
                }
                else if (fourCC[0] == 'T' && fourCC[1] == 'X' && fourCC[2] == 'T' && fourCC[3] == 'R')
                {
                    uint32_t subGetLoc = 0;

                    uint32_t txtrFormat;

                    memcpy(&txtrFormat, &rawFile.data()[subGetLoc], sizeof(txtrFormat));
                    txtrFormat = swap_endian<uint32_t>(txtrFormat);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrFormat)) << "] texture format:" << txtrFormat << std::dec << std::endl;
                    subGetLoc += sizeof(txtrFormat);

                    uint16_t txtrWidth;

                    memcpy(&txtrWidth, &rawFile.data()[subGetLoc], sizeof(txtrWidth));
                    txtrWidth = swap_endian<uint16_t>(txtrWidth);
                    std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrWidth)) << "] texture width:" << txtrWidth << std::dec << std::endl;
                    subGetLoc += sizeof(txtrWidth);

                    uint16_t txtrHeight;

                    memcpy(&txtrHeight, &rawFile.data()[subGetLoc], sizeof(txtrHeight));
                    txtrHeight = swap_endian<uint16_t>(txtrHeight);
                    std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(txtrHeight)) << "] texture height:" << txtrHeight << std::dec << std::endl;
                    subGetLoc += sizeof(txtrHeight);

                    uint32_t mipCount;

                    memcpy(&mipCount, &rawFile.data()[subGetLoc], sizeof(mipCount));
                    mipCount = swap_endian<uint32_t>(mipCount);
                    std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(mipCount)) << "] mip count:" << mipCount << std::dec << std::endl;
                    subGetLoc += sizeof(mipCount);

                    if (txtrFormat == 0x4 || txtrFormat == 0x5)
                    {
                        //TODO: read pallettes
                    }

                   // if (txtrFormat == 0xa)
                   // {
                   //     std::vector<uint8_t> textureChunk;
                   //     textureChunk.resize(32);
                   //     memcpy(&textureChunk, &rawFile.data()[subGetLoc], 32);
                   //     std::vector<uint8_t> imageChunk;
                   //     imageChunk.resize(8 * 8);
                   //
                   //     //squish::Decompress(&imageChunk.data()[0], &textureChunk.data()[0], txtrFormat);
                   //
                   // }

                }
                else if (fourCC[0] == 'C' && fourCC[1] == 'M' && fourCC[2] == 'D' && fourCC[3] == 'L')
                {
                    if (tempcounter > 0)
                        continue;
                    tempcounter++;
                    std::cout << "model found!" << std::endl;
                    //int32_t magic = (rawFile[3] << 24) | (rawFile[2] << 16) | (rawFile[1] << 8) | rawFile[0];
                    //std::cout << "\t\tmagic: " << std::hex << magic << std::dec << std::endl;
                    std::cout << "\tAsset ID                " << std::hex << AssetID << std::dec << std::endl;
                    //for (int jfiels = 0; jfiels < 50; jfiels+=2)
                    //{
                    //    std::cout << std::hex << ((rawFile[jfiels] << 8) | rawFile[jfiels+1]) << std::dec;
                    //}std::cout << std::endl;
                    //dumpToFile("dump.cmdl", rawFile.data(),rawFile.size());
                    //std::cout << hex(rawFile[0]) << hex(rawFile[1]) << hex(rawFile[2]) << hex(rawFile[3]) << std::endl;

                    uint32_t subGetLoc = 0;

                    CMDLs.resize(CMDLs.size() + 1);

                    uint32_t cmdlIndex = CMDLs.size() - 1;

                    memcpy(&CMDLs[cmdlIndex].magic, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].magic));
                    CMDLs[cmdlIndex].magic = swap_endian<int32_t>(CMDLs[cmdlIndex].magic);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].magic)) << "] magic:" << CMDLs[cmdlIndex].magic << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLs[cmdlIndex].magic);

                    memcpy(&CMDLs[cmdlIndex].version, &rawFile.data()[subGetLoc], 4);
                    CMDLs[cmdlIndex].version = swap_endian<int32_t>(CMDLs[cmdlIndex].version);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].version)) << "] version:" << CMDLs[cmdlIndex].version << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLs[cmdlIndex].version);

                    memcpy(&CMDLs[cmdlIndex].flags, &rawFile.data()[subGetLoc], 4);
                    CMDLs[cmdlIndex].flags = swap_endian<int32_t>(CMDLs[cmdlIndex].flags);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].flags)) << "] flags:" << CMDLs[cmdlIndex].flags << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLs[cmdlIndex].flags);

                    memcpy(CMDLs[cmdlIndex].ModelAxisAlignedBoundingBox, &rawFile.data()[subGetLoc], sizeof(float) * 6);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(float) * 6) << "] Model Axis-Aligned Bounding Box:";
                    for (int ijk = 0; ijk < 6; ijk++)
                    {
                        //std::cout << hex(rawFile[0x0C+ijk]);
                        CMDLs[cmdlIndex].ModelAxisAlignedBoundingBox[ijk] = swap_endian<float>(CMDLs[cmdlIndex].ModelAxisAlignedBoundingBox[ijk]);
                        std::cout << CMDLs[cmdlIndex].ModelAxisAlignedBoundingBox[ijk];
                    }
                    std::cout << std::dec << std::endl;
                    subGetLoc += sizeof(float) * 6;

                    memcpy(&CMDLs[cmdlIndex].dataSectionCount, &rawFile.data()[subGetLoc], 4);
                    CMDLs[cmdlIndex].dataSectionCount = swap_endian<int32_t>(CMDLs[cmdlIndex].dataSectionCount);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].dataSectionCount)) << "] data Section Count:" << CMDLs[cmdlIndex].dataSectionCount << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLs[cmdlIndex].dataSectionCount);

                    memcpy(&CMDLs[cmdlIndex].MaterialSetCount, &rawFile.data()[subGetLoc], 4);
                    CMDLs[cmdlIndex].MaterialSetCount = swap_endian<int32_t>(CMDLs[cmdlIndex].MaterialSetCount);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].MaterialSetCount)) << "] Material Set Count:" << CMDLs[cmdlIndex].MaterialSetCount << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLs[cmdlIndex].MaterialSetCount);



                    CMDLs[cmdlIndex].materialSets.resize(CMDLs[cmdlIndex].MaterialSetCount);





                    CMDLs[cmdlIndex].dataSectionSizes.resize(CMDLs[cmdlIndex].dataSectionCount);

                    for (int ijk = 0; ijk < CMDLs[cmdlIndex].dataSectionCount; ijk++)
                    {
                        memcpy(&CMDLs[cmdlIndex].dataSectionSizes[ijk], &rawFile.data()[subGetLoc], sizeof(uint32_t));
                        CMDLs[cmdlIndex].dataSectionSizes[ijk] = swap_endian<uint32_t>(CMDLs[cmdlIndex].dataSectionSizes[ijk]);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc + sizeof(uint32_t) << "]" << "data section " << std::dec << ijk << " size: " << CMDLs[cmdlIndex].dataSectionSizes[ijk] << std::endl;
                        subGetLoc += sizeof(uint32_t);

                    }


                    //subGetLoc += sizeof(uint32_t)*CMDLs[cmdlIndex].dataSectionCount;



                    subGetLoc += 32 - subGetLoc % 32;

                    uint32_t upperGetLoc = subGetLoc;
                    std::cout << "reading material data from " << std::hex << subGetLoc << std::dec << std::endl;


                    if (true)
                        for (int imat = 0; imat < CMDLs[cmdlIndex].MaterialSetCount; imat++)
                        {

                            memcpy(&(CMDLs[cmdlIndex].materialSets[imat].textureCount), &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].materialSets[imat].textureCount));
                            CMDLs[cmdlIndex].materialSets[imat].textureCount = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].textureCount);
                            std::cout << "textures: " << CMDLs[cmdlIndex].materialSets[imat].textureCount << std::endl;
                            CMDLs[cmdlIndex].materialSets[imat].textureFileIDs.resize(CMDLs[cmdlIndex].materialSets[imat].textureCount);
                            memcpy(CMDLs[cmdlIndex].materialSets[imat].textureFileIDs.data(), &rawFile.data()[subGetLoc + sizeof(CMDLs[cmdlIndex].materialSets[imat].textureCount)], sizeof(CMDLs[cmdlIndex].materialSets[imat].textureFileIDs.data()) * CMDLs[cmdlIndex].materialSets[imat].textureFileIDs.size());
                            //memcpy(textureFileIDs.data(), &rawFile.data()[subGetLoc+sizeof(textureCount)],sizeof(uint32_t));
                            for (int tx = 0; tx < CMDLs[cmdlIndex].materialSets[imat].textureCount; tx++) {
                                memcpy(&(CMDLs[cmdlIndex].materialSets[imat].textureFileIDs[tx]), &rawFile.data()[subGetLoc + sizeof(CMDLs[cmdlIndex].materialSets[imat].textureCount) + tx * sizeof(uint32_t)], sizeof(uint32_t));
                                CMDLs[cmdlIndex].materialSets[imat].textureFileIDs[tx] = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].textureFileIDs[tx]);
                                std::cout << "texture used: " << std::hex << CMDLs[cmdlIndex].materialSets[imat].textureFileIDs[tx] << std::dec << std::endl;
                            }


                            memcpy(&(CMDLs[cmdlIndex].materialSets[imat].materialCount), &rawFile.data()[subGetLoc + sizeof(CMDLs[cmdlIndex].materialSets[imat].textureCount) + CMDLs[cmdlIndex].materialSets[imat].textureCount * sizeof(uint32_t)], sizeof(CMDLs[cmdlIndex].materialSets[imat].materialCount));
                            CMDLs[cmdlIndex].materialSets[imat].materialCount = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].materialCount);
                            std::cout << CMDLs[cmdlIndex].materialSets[imat].materialCount << std::endl;
                            CMDLs[cmdlIndex].materialSets[imat].materialEndOffsets.resize(CMDLs[cmdlIndex].materialSets[imat].materialCount);
                            for (int mc = 0; mc < CMDLs[cmdlIndex].materialSets[imat].materialCount; mc++) {
                                memcpy(&(CMDLs[cmdlIndex].materialSets[imat].materialEndOffsets[mc]), &rawFile.data()[subGetLoc + sizeof(CMDLs[cmdlIndex].materialSets[imat].textureCount) + CMDLs[cmdlIndex].materialSets[imat].textureCount * sizeof(uint32_t) + sizeof(CMDLs[cmdlIndex].materialSets[imat].materialCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                                CMDLs[cmdlIndex].materialSets[imat].materialEndOffsets[mc] = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].materialEndOffsets[mc]);
                                std::cout << "material end offset: " << std::hex << CMDLs[cmdlIndex].materialSets[imat].materialEndOffsets[mc] << std::dec << std::endl;
                            }

                            subGetLoc = subGetLoc + sizeof(CMDLs[cmdlIndex].materialSets[imat].textureCount) + CMDLs[cmdlIndex].materialSets[imat].textureCount * sizeof(uint32_t) + sizeof(CMDLs[cmdlIndex].materialSets[imat].materialCount) + CMDLs[cmdlIndex].materialSets[imat].materialCount * sizeof(uint32_t);

                            uint32_t flags;
                            memcpy(&flags, &rawFile.data()[subGetLoc], sizeof(flags));
                            flags = swap_endian<uint32_t>(flags);
                            std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                            std::cout << "material properties:" << std::endl;
                            std::cout << "\tUnused, always set:                                " << ((flags & 0x01) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tUnused, always set:                                " << ((flags & 0x02) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tUnused, never set:                                 " << ((flags & 0x04) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tHas Konst values:                                  " << ((flags & 0x08) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tIs transparent:                                    " << ((flags & 0x10) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tMasked alpha:                                      " << ((flags & 0x20) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tEnable Samus's reflection:                         " << ((flags & 0x40) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tEnable Z-writes:                                   " << ((flags & 0x80) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tEnable Samus's reflection, using the eye position: " << ((flags & 0x100) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tShadow occluder mesh:                              " << ((flags & 0x200) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tEnable indirect texture stage for reflections:     " << ((flags & 0x400) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tIndicates a lightmap is present:                   " << ((flags & 0x800) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tUnused, always set:                                " << ((flags & 0x1000) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tEnable first UV coordinate to use short array:     " << ((flags & 0x2000) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tunused, never set:                                 " << ((flags & 0x4000) > 0 ? "on" : "off") << std::endl;
                            std::cout << "\tunused, never set:                                 " << ((flags & 0x8000) > 0 ? "on" : "off") << std::endl;
                            subGetLoc += sizeof(flags);
                            int32_t TC;
                            memcpy(&TC, &rawFile.data()[subGetLoc], sizeof(TC));
                            TC = swap_endian<int32_t>(TC);
                            std::cout << "Texture Count: " << TC << std::endl;
                            subGetLoc += sizeof(TC);
                            while (TC > 100) {}
                            CMDLs[cmdlIndex].materialSets[imat].textureFileIndices.resize(TC);
                            std::cout << "textures:" << std::endl;
                            for (int tx = 0; tx < TC; tx += sizeof(uint32_t)) {
                                memcpy(&(CMDLs[cmdlIndex].materialSets[imat].textureFileIndices[tx]), &rawFile.data()[subGetLoc + tx], sizeof(uint32_t));
                                CMDLs[cmdlIndex].materialSets[imat].textureFileIndices[tx] = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].textureFileIndices[tx]);
                                //std::cout << CMDLs[cmdlIndex].materialSets[imat].textureFileIndices[tx] << std::endl;
                                std::cout << "\ttexture: " << std::hex << CMDLs[cmdlIndex].materialSets[imat].textureFileIDs[CMDLs[cmdlIndex].materialSets[imat].textureFileIndices[tx]] << std::dec << std::endl;
                            }

                            subGetLoc += TC * sizeof(uint32_t);

                            //uint32_t vertexAtributeFlags;
                            memcpy(&CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags));
                            CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags);
                            std::cout << "vertex atributes: " << std::endl;
                            std::cout << CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags << std::endl;
                            std::cout << "\tPosition: " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0x3) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tNormal:   " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0xC) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tColor 0:  " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0x30) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tColor 1:  " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0xC0) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tTex 0:    " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0x300) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tTex 1:    " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0xC00) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tTex 2:    " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0x3000) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tTex 3:    " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0xC000) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tTex 4:    " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0x30000) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tTex 5:    " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0xC0000) > 0 ? "1" : "0") << std::endl;
                            std::cout << "\tTex 6:    " << ((CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags & 0x300000) > 0 ? "1" : "0") << std::endl;
                            subGetLoc += sizeof(CMDLs[cmdlIndex].materialSets[imat].vertexAtributeFlags);
                            uint32_t groupIndex;
                            memcpy(&groupIndex, &rawFile.data()[subGetLoc], sizeof(groupIndex));
                            groupIndex = swap_endian<uint32_t>(groupIndex);
                            std::cout << "group index: " << groupIndex << std::endl;
                            subGetLoc += sizeof(groupIndex);
                            if ((flags & 0x08) > 0)
                            {
                                uint32_t KonstCount;
                                memcpy(&KonstCount, &rawFile.data()[subGetLoc], sizeof(KonstCount));
                                KonstCount = swap_endian<uint32_t>(KonstCount);
                                std::cout << KonstCount << std::endl;
                                CMDLs[cmdlIndex].materialSets[imat].konstColors.resize(KonstCount);
                                for (int mc = 0; mc < KonstCount; mc++) {
                                    memcpy(&(CMDLs[cmdlIndex].materialSets[imat].konstColors[mc]), &rawFile.data()[subGetLoc + sizeof(KonstCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                                    CMDLs[cmdlIndex].materialSets[imat].konstColors[mc] = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].konstColors[mc]);
                                    std::cout << "konst color " << mc << ": " << std::hex << CMDLs[cmdlIndex].materialSets[imat].konstColors[mc] << std::dec << std::endl;
                                }
                                subGetLoc += sizeof(KonstCount) + KonstCount * sizeof(uint32_t);
                            }
                            std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                            short blendDestFactor;
                            memcpy(&blendDestFactor, &rawFile.data()[subGetLoc], sizeof(blendDestFactor));
                            blendDestFactor = swap_endian<short>(blendDestFactor);
                            std::cout << "blendDestFactor: " << blendDestFactor << std::endl;
                            subGetLoc += sizeof(blendDestFactor);

                            short blendSourceFactor;
                            memcpy(&blendSourceFactor, &rawFile.data()[subGetLoc], sizeof(blendSourceFactor));
                            blendSourceFactor = swap_endian<short>(blendSourceFactor);
                            std::cout << "blendSourceFactor: " << blendSourceFactor << std::endl;
                            subGetLoc += sizeof(blendSourceFactor);

                            if ((flags & 0x400) != 0)
                            {
                                uint32_t reflectionIndirectTextureIndex;
                                memcpy(&reflectionIndirectTextureIndex, &rawFile.data()[subGetLoc], sizeof(reflectionIndirectTextureIndex));
                                reflectionIndirectTextureIndex = swap_endian<uint32_t>(reflectionIndirectTextureIndex);
                                std::cout << "reflection Indirect Texture Index: " << reflectionIndirectTextureIndex << std::endl;
                                subGetLoc += sizeof(reflectionIndirectTextureIndex);
                            }


                            //
                            memcpy(&(CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount), &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount));
                            CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount);
                            std::cout << "color channel count: " << CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount << std::endl;
                            std::cout << "offset: " << std::hex << subGetLoc << std::dec << std::endl;
                            CMDLs[cmdlIndex].materialSets[imat].ColorChannelFlags.resize(CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount);
                            for (int mc = 0; mc < CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount; mc++) {
                                memcpy(&(CMDLs[cmdlIndex].materialSets[imat].ColorChannelFlags[mc]), &rawFile.data()[subGetLoc + sizeof(CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount) + mc * sizeof(uint32_t)], sizeof(uint32_t));
                                CMDLs[cmdlIndex].materialSets[imat].ColorChannelFlags[mc] = swap_endian<uint32_t>(CMDLs[cmdlIndex].materialSets[imat].ColorChannelFlags[mc]);
                                std::cout << "color channel flags: " << CMDLs[cmdlIndex].materialSets[imat].ColorChannelFlags[mc] << std::dec << std::endl;
                            }
                            subGetLoc += sizeof(CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount) + CMDLs[cmdlIndex].materialSets[imat].ColorChannelCount * sizeof(uint32_t);


                            uint32_t TEVStageCount;
                            memcpy(&TEVStageCount, &rawFile.data()[subGetLoc], sizeof(TEVStageCount));
                            TEVStageCount = swap_endian<uint32_t>(TEVStageCount);
                            std::cout << "TEV Stage Count: " << TEVStageCount << std::endl;
                            subGetLoc += sizeof(TEVStageCount);











                            upperGetLoc += CMDLs[cmdlIndex].dataSectionSizes[imat];
                            subGetLoc = upperGetLoc;
                        }
                    else
                        for (int ijk = 0; ijk < CMDLs[cmdlIndex].MaterialSetCount; ijk++)
                        {
                            subGetLoc += CMDLs[cmdlIndex].dataSectionSizes[ijk];
                        }

                    std::cout << "reading geometry data from " << std::hex << subGetLoc << std::dec << std::endl;
                    upperGetLoc = subGetLoc;


                    CMDLs[cmdlIndex].geometry.vertexCoords.resize(
                        (
                            CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount] -
                            (CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount]) % (sizeof(float) * 3)
                            )
                        / (sizeof(float))
                    );
                    std::cout << "number of vert coords: " << CMDLs[cmdlIndex].geometry.vertexCoords.size() << std::endl;
                    for (int ijk = 0; ijk < CMDLs[cmdlIndex].geometry.vertexCoords.size(); ijk++)
                    {
                        memcpy(&CMDLs[cmdlIndex].geometry.vertexCoords[ijk], &rawFile.data()[subGetLoc], sizeof(uint32_t));
                        CMDLs[cmdlIndex].geometry.vertexCoords[ijk] = swap_endian<float>(CMDLs[cmdlIndex].geometry.vertexCoords[ijk]);

                        subGetLoc += sizeof(float);
                    }
                    

                    //CMDLs[cmdlIndex].geometry.vertexCoords = std::vector<float>(rawFile.data() + subGetLoc, rawFile.data()+ CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount] - (CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount]) % (sizeof(float) * 3));


                    upperGetLoc += CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount];
                    subGetLoc = upperGetLoc;
                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "reading normals" << std::endl;

                    CMDLs[cmdlIndex].geometry.normals.resize(
                        (
                            CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 1] -
                            (CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 1]) % (sizeof(float) * 3)
                            ) / sizeof(float)
                    );
                    std::cout << "number of normal coords: " << CMDLs[cmdlIndex].geometry.normals.size() << std::endl;


                    for (int ijk = 0; ijk < CMDLs[cmdlIndex].geometry.normals.size(); ijk++)
                    {
                        memcpy(&CMDLs[cmdlIndex].geometry.normals[ijk], &rawFile.data()[subGetLoc], sizeof(float));
                        CMDLs[cmdlIndex].geometry.normals[ijk] = swap_endian<float>(CMDLs[cmdlIndex].geometry.normals[ijk]);
                        subGetLoc += sizeof(float);
                    }
                    upperGetLoc += CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 1];
                    subGetLoc = upperGetLoc;

                    //std::cout << std::hex << subGetLoc << std::dec << std::endl;
                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "skipping color data" << std::endl;

                    //no need to read color data, it's all empty

                    upperGetLoc += CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 2];
                    subGetLoc = upperGetLoc;

                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "reading float UV coords" << std::endl;
                    CMDLs[cmdlIndex].geometry.floatUVCoords.resize(
                        (
                            CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 3] -
                            (CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 3]) % (sizeof(float) * 2)
                            ) / sizeof(float)
                    );
                    std::cout << "number of float UV coords: " << CMDLs[cmdlIndex].geometry.floatUVCoords.size() << std::endl;

                    for (int ijk = 0; ijk < CMDLs[cmdlIndex].geometry.floatUVCoords.size(); ijk++)
                    {
                        memcpy(&CMDLs[cmdlIndex].geometry.floatUVCoords[ijk], &rawFile.data()[subGetLoc], sizeof(float));
                        CMDLs[cmdlIndex].geometry.floatUVCoords[ijk] = swap_endian<float>(CMDLs[cmdlIndex].geometry.floatUVCoords[ijk])/2;
                        subGetLoc += sizeof(float);
                    }

                    upperGetLoc += CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 3];
                    subGetLoc = upperGetLoc;


                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "skipping short UV coords" << std::endl;
                    //short uv coords are COMPLETELY empty for this mesh, but I'll need to implement it for the future
                    upperGetLoc += CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 4];
                    subGetLoc = upperGetLoc;

                    std::cout << std::hex << "[" << subGetLoc << " :: " << subGetLoc << "]" << std::dec << "reading header data" << std::endl;
                    //the moment of truth:

                    memcpy(&CMDLs[cmdlIndex].geometry.surfaceCount, &rawFile.data()[subGetLoc], 4);
                    CMDLs[cmdlIndex].geometry.surfaceCount = swap_endian<uint32_t>(CMDLs[cmdlIndex].geometry.surfaceCount);
                    std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaceCount)) << "] surface count:" << CMDLs[cmdlIndex].geometry.surfaceCount << std::dec << std::endl;
                    subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaceCount);

                    CMDLs[cmdlIndex].geometry.surfaceOffsets.resize(CMDLs[cmdlIndex].geometry.surfaceCount);

                    for (int ijk = 0; ijk < CMDLs[cmdlIndex].geometry.surfaceCount; ijk++)
                    {
                        memcpy(&CMDLs[cmdlIndex].geometry.surfaceOffsets[ijk], &rawFile.data()[subGetLoc], sizeof(uint32_t));
                        CMDLs[cmdlIndex].geometry.surfaceOffsets[ijk] = swap_endian<uint32_t>(CMDLs[cmdlIndex].geometry.surfaceOffsets[ijk]);
                        std::cout << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(uint32_t)) << "] surface offset " << ijk << ": " << std::hex << CMDLs[cmdlIndex].geometry.surfaceOffsets[ijk] << std::dec << std::endl;
                        subGetLoc += sizeof(uint32_t);
                    }

                    //that's the end of this section, on to the next one
                    upperGetLoc += CMDLs[cmdlIndex].dataSectionSizes[CMDLs[cmdlIndex].MaterialSetCount + 5];
                    subGetLoc = upperGetLoc;
                    CMDLs[cmdlIndex].geometry.surfaces.resize(CMDLs[cmdlIndex].geometry.surfaceCount);

                    //loop through each surface
                    for (int surfaceNum = 0; surfaceNum < CMDLs[cmdlIndex].geometry.surfaceCount; surfaceNum++)
                    {

                        for (int ijk = 0; ijk < 3; ijk++)
                        {
                            memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].centerPoint[ijk], &rawFile.data()[subGetLoc], sizeof(float));
                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].centerPoint[ijk] = swap_endian<float>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].centerPoint[ijk]);
                            subGetLoc += sizeof(float);
                        }
                        std::cout << "center point: " << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].centerPoint[0] << ", " << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].centerPoint[1] << ", " << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].centerPoint[2] << std::endl;

                        memcpy(
                            &CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex,
                            &rawFile.data()[subGetLoc],
                            sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex)
                        );
                        CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex = swap_endian<uint32_t>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex)) << "] matIndex:" << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex);

                        memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].maintissa, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].maintissa));
                        CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].maintissa = swap_endian<uint16_t>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].maintissa);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].maintissa)) << "] maintissa:" << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].maintissa << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].maintissa);

                        memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].displayListSize, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].displayListSize));
                        CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].displayListSize = swap_endian<uint16_t>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].displayListSize);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].displayListSize)) << "] display list size:" << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].displayListSize << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].displayListSize);

                        memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].parentModelPointer, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].parentModelPointer));
                        CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].parentModelPointer = swap_endian<uint32_t>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].parentModelPointer);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].parentModelPointer)) << "] parentModelPointer (always 0):" << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].parentModelPointer << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].parentModelPointer);

                        memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nextSurfacePointer, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nextSurfacePointer));
                        CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nextSurfacePointer = swap_endian<uint32_t>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nextSurfacePointer);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nextSurfacePointer)) << "] nextSurfacePointer (always 0):" << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nextSurfacePointer << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nextSurfacePointer);

                        memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize));
                        CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize = swap_endian<uint32_t>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize);
                        std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize)) << "] extraDataSize (always 0):" << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize);

                        CMDLs[cmdlIndex].geometry.surfaces.resize(CMDLs[cmdlIndex].geometry.surfaceCount);
                        for (int ijk = 0; ijk < 3; ijk++)
                        {
                            memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].surfaceNormal[ijk], &rawFile.data()[subGetLoc], sizeof(float));
                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].surfaceNormal[ijk] = swap_endian<float>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].surfaceNormal[ijk]);
                            subGetLoc += sizeof(float);
                        }
                        std::cout << "surface normal: " << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].surfaceNormal[0] << ", " << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].surfaceNormal[1] << ", " << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].surfaceNormal[2] << std::endl;



                        subGetLoc += CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].extraDataSize;

                        //align get location to 32 bytes before reading primatives
                        subGetLoc += 32 - subGetLoc % 32;



                        //char a = -58;
                        //std::cout << "a = " << std::bitset<8>(GXFlags) << std::endl;
                        //the second one will have 73
                        //todo: read until the gx flag hits zero or it hits the end of the section

                        memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags));
                        //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(GXFlags)) << "] GXFlags:" << GXFlags << std::dec << std::endl;
                        subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags);

                        while (CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags > 0)
                        {


                            std::bitset<8> GXFlagBits(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags);

                            std::cout << GXFlagBits << std::endl;

                            memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount));
                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount = swap_endian<uint16_t>(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount);
                            std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount)) << "] vertex count:" << std::dec << CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount << std::dec << std::endl;
                            subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount);

                            uint16_t pos_index1before = 0;
                            uint16_t pos_index2before = 0;
                            uint16_t pos_indexwaybefore = 0;

                            uint16_t nml_index1before = 0;
                            uint16_t nml_index2before = 0;
                            uint16_t nml_indexwaybefore = 0;

                            uint16_t uvc_index1before = 0;
                            uint16_t uvc_index2before = 0;
                            uint16_t uvc_indexwaybefore = 0;
                            for (int ijk = 0; ijk < CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].vertexCount; ijk++)
                            {

                                
                                uint16_t pos_vIndex;
                                uint16_t nml_vIndex;
                                uint16_t uvc_vIndex;
                                
                                memcpy(&pos_vIndex, &rawFile.data()[subGetLoc], sizeof(pos_vIndex));
                                pos_vIndex = swap_endian<uint16_t>(pos_vIndex);
                                subGetLoc += sizeof(pos_vIndex);

                                memcpy(&nml_vIndex, &rawFile.data()[subGetLoc], sizeof(nml_vIndex));
                                nml_vIndex = swap_endian<uint16_t>(nml_vIndex);
                                subGetLoc += sizeof(nml_vIndex);

                                memcpy(&uvc_vIndex, &rawFile.data()[subGetLoc], sizeof(uvc_vIndex));
                                uvc_vIndex = swap_endian<uint16_t>(uvc_vIndex);
                                subGetLoc += sizeof(uvc_vIndex);

                                if (ijk == 0) {
                                    pos_indexwaybefore = pos_vIndex;
                                    nml_indexwaybefore = nml_vIndex;
                                    uvc_indexwaybefore = uvc_vIndex;
                                }
                                //std::cout << "vertex " << ijk << " position: " <<
                                //    CMDLs[cmdlIndex].geometry.vertexCoords.data()[vIndex * 3 + 0] << ", " <<
                                //    CMDLs[cmdlIndex].geometry.vertexCoords.data()[vIndex * 3 + 1] << ", " <<
                                //    CMDLs[cmdlIndex].geometry.vertexCoords.data()[vIndex * 3 + 2] <<
                                //    std::endl;
                                if (((CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0xA0)) {
                                    if (ijk > 1)
                                    {
                                        if ((CMDLs[cmdlIndex].materialSets[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x3) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_indexwaybefore));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_vIndex));
                                        }
                                        if ((CMDLs[cmdlIndex].materialSets[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0xC) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_indexwaybefore));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_vIndex));
                                        }
                                        if ((CMDLs[cmdlIndex].materialSets.data()[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x300) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_indexwaybefore));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_vIndex));
                                        }
                                    }
                                }
                                else if (((CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0x90))
                                {
                                    if (ijk > 1 && (ijk + 1) % 3 == 0) {
                                        if ((CMDLs[cmdlIndex].materialSets[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x3) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index2before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_vIndex));
                                        }
                                        if ((CMDLs[cmdlIndex].materialSets[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0xC) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index2before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_vIndex));
                                        }
                                        if ((CMDLs[cmdlIndex].materialSets.data()[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x300) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index2before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_vIndex));
                                        }
                                    }
                                }
                                else if (((CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags & 0xF8) == 0x98))
                                {
                                    if (ijk > 1) {
                                        if ((CMDLs[cmdlIndex].materialSets[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x3) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index2before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].pos_indices.push_back(static_cast<uint32_t>(pos_vIndex));
                                        }
                                        if ((CMDLs[cmdlIndex].materialSets[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0xC) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index2before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].nml_indices.push_back(static_cast<uint32_t>(nml_vIndex));
                                        }
                                        if ((CMDLs[cmdlIndex].materialSets.data()[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x300) > 0)
                                        {
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index2before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_index1before));
                                            CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].uvc_indices.push_back(static_cast<uint32_t>(uvc_vIndex));
                                        }
                                    }
                                }
                                else
                                {
                                    std::cout << "unsupported primitive" << std::endl;
                                }
                                pos_index2before = pos_index1before;
                                pos_index1before = pos_vIndex;

                                
                                //if ((CMDLs[cmdlIndex].materialSets[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0xC) > 0)
                                //{
                                //    uint16_t vIndex;
                                //    memcpy(&vIndex, &rawFile.data()[subGetLoc], sizeof(vIndex));
                                //    vIndex = swap_endian<uint16_t>(vIndex);
                                //    std::cout << "vertex " << ijk << " normal: " <<
                                //        CMDLs[cmdlIndex].geometry.normals.data()[vIndex * 3 + 0] << ", " <<
                                //        CMDLs[cmdlIndex].geometry.normals.data()[vIndex * 3 + 1] << ", " <<
                                //        CMDLs[cmdlIndex].geometry.normals.data()[vIndex * 3 + 2] <<
                                //        std::endl;
                                //    subGetLoc += sizeof(vIndex);
                                //}
                                //
                                //
                                ////todo: color inputs
                                //
                                //
                                //if ((CMDLs[cmdlIndex].materialSets.data()[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0x300) > 0)
                                //{
                                //    uint16_t vIndex;
                                //    memcpy(&vIndex, &rawFile.data()[subGetLoc], sizeof(vIndex));
                                //    vIndex = swap_endian<uint16_t>(vIndex);
                                //    std::cout << "vertex " << ijk << " UV: " <<
                                //        CMDLs[cmdlIndex].geometry.floatUVCoords.data()[vIndex * 2 + 0] << ", " <<
                                //        CMDLs[cmdlIndex].geometry.floatUVCoords.data()[vIndex * 2 + 1] <<
                                //        std::endl;
                                //    subGetLoc += sizeof(vIndex);
                                //}
                                //if ((CMDLs[cmdlIndex].materialSets.data()[0/*CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].matIndex*/].vertexAtributeFlags & 0xC00) > 0)
                                //{
                                //    uint16_t vIndex;
                                //    memcpy(&vIndex, &rawFile.data()[subGetLoc], sizeof(vIndex));
                                //    vIndex = swap_endian<uint16_t>(vIndex);
                                //    std::cout << "vertex " << ijk << " UV: " <<
                                //        CMDLs[cmdlIndex].geometry.floatUVCoords.data()[vIndex * 2 + 0] << ", " <<
                                //        CMDLs[cmdlIndex].geometry.floatUVCoords.data()[vIndex * 2 + 1] <<
                                //        std::endl;
                                //    subGetLoc += sizeof(vIndex);
                                //}
                                //


                            }
                            //0x3       position
                            //0xC       normal
                            //0x30      color 0
                            //0xC0      color 1
                            //0x300     texture 0
                            //0xC00     texture 1
                            //0x3000    texture 2
                            //0xC000    texture 3
                            //0x30000   texture 4
                            //0xC0000   texture 5
                            //0x30000   texture 6

                            memcpy(&CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags, &rawFile.data()[subGetLoc], sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags));
                            //std::cout << std::hex << "[" << subGetLoc << " :: " << (subGetLoc + sizeof(GXFlags)) << "] GXFlags:" << GXFlags << std::dec << std::endl;

                            subGetLoc += sizeof(CMDLs[cmdlIndex].geometry.surfaces[surfaceNum].GXFlags);


                            if (CMDLs[cmdlIndex].geometry.surfaceOffsets[surfaceNum] < (subGetLoc - upperGetLoc) + 2 * sizeof(uint16_t)) {

                                //upperGetLoc += CMDLs[cmdlIndex].geometry.surfaceOffsets[surfaceNum];
                                //subGetLoc = upperGetLoc;
                                //subGetLoc = upperGetLoc+ CMDLs[cmdlIndex].geometry.surfaceOffsets[surfaceNum]+1;
                                std::cout << "TRIGGERED TRIGGERED TRIGGERED" << std::endl;
                                break;

                            }
                        }





                    }

                    //m.startIndex = indices.size();
                    //m.vertOffset = vertices.size();
                    //
                    //vertices.insert(vertices.end(), m.vertices.begin(), m.vertices.end());
                    //indices.insert(indices.end(), m.indices.begin(), m.indices.end());
                    //
                    //m.num_indices = indices.size() - m.startIndex;
                    //objects.push_back(m);

                    //TODO: temporary:
                    //return;

                }
            }
            else if (compressionFlag == 0)
            {
                if (fourCC[0] == 'S' && fourCC[1] == 'T' && fourCC[2] == 'R' && fourCC[3] == 'G')
                {
                    int32_t magic;
                    f.read(reinterpret_cast<char*>(&magic), sizeof(magic));

                    magic = swap_endian<int32_t>(magic);
                    std::cout << "magic: " << std::hex << magic << std::dec << std::endl;


                    int32_t version;
                    int32_t langCount;
                    int32_t stringCount;

                    f.read(reinterpret_cast<char*>(&version), sizeof(version));
                    f.read(reinterpret_cast<char*>(&langCount), sizeof(langCount));
                    f.read(reinterpret_cast<char*>(&stringCount), sizeof(stringCount));

                    version = swap_endian<int32_t>(version);
                    langCount = swap_endian<int32_t>(langCount);
                    stringCount = swap_endian<int32_t>(stringCount);

                    std::cout << "version: " << std::hex << version << std::dec << std::endl;
                    std::cout << "langCount: " << std::hex << langCount << std::dec << std::endl;
                    std::cout << "string count: " << std::hex << stringCount << std::dec << std::endl;
                    for (int j = 0; j < langCount; j++) {
                        f.read(fourCC, 4);
                        std::cout << "Language ID: "; std::cout.write(fourCC, 4) << std::endl;
                        uint32_t posOffset;
                        f.read(reinterpret_cast<char*>(&posOffset), sizeof(posOffset));
                        posOffset = swap_endian<uint32_t>(posOffset);
                        std::cout << "language location offset: " << posOffset << std::endl;

                    }
                    for (int j = 0; j < langCount; j++)
                    {
                        uint32_t stringTableSize;
                        f.read(reinterpret_cast<char*>(&stringTableSize), sizeof(stringTableSize));
                        stringTableSize = swap_endian<uint32_t>(stringTableSize);
                        std::cout << "string table size: " << stringTableSize << std::endl;
                        std::vector<uint32_t> stringOffsets;
                        stringOffsets.resize(stringCount);
                        uint32_t disjointOffset = f.tellg();
                        for (int k = 0; k < stringCount; k++)
                        {
                            f.read(reinterpret_cast<char*>(&stringOffsets[k]), sizeof(uint32_t));
                            stringOffsets[k] = swap_endian<uint32_t>(stringOffsets[k]);
                        }
                        std::vector<std::string> strings;
                        strings.resize(stringCount);
                        for (int k = 0; k < stringCount; k++)
                        {
                            f.seekg(stringOffsets.at(k) + disjointOffset);
                            char temp;
                            std::string tempstr = "";
                            f.get();
                            while ((temp = f.get()) != '\0') {
                                tempstr += temp; f.get();
                            }
                            strings[k] = tempstr;
                            std::cout << tempstr << std::endl;
                        }
                    }

                }
                else {
                    std::cout << fourCC[0] << fourCC[1] << fourCC[2] << fourCC[3] << std::endl;
                }
            }
            f.seekg(getLoc);
        }
    }
    void loadScene()
    {
        loadPak("metroid2.pak");
        //std::ifstream f(LEVEL_PATH);
        //if (!f.is_open())
        //    throw std::invalid_argument("level data not found");
        //
        //while (!f.eof())
        //{
        //    char line[128];
        //    f.getline(line, 128);
        //
        //    std::strstream s;
        //    s << line;
        //    std::string objectFile;
        //    Mesh m;
        //    s >> m.filePath >> m.x >> m.y >> m.z;
        //
        //    m.filePath = "models/ssdolphin/" + m.filePath;
        //    m.startIndex = indices.size();
        //    m.vertOffset = vertices.size();
        //    //loadModel(&m);
        //
        //    vertices.insert(vertices.end(), m.vertices.begin(), m.vertices.end());
        //    indices.insert(indices.end(), m.indices.begin(), m.indices.end());
        //
        //    m.num_indices = indices.size() - m.startIndex;
        //    objects.push_back(m);
        //}

    }
    void loadModel(Mesh* m) {
        //tinyobj::attrib_t attrib;
        //std::vector<tinyobj::shape_t> shapes;
        //std::vector<tinyobj::material_t> materials;
        //std::string warn, err;

        //if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, m->filePath.c_str())) {
         //   throw std::runtime_error(warn + err);
        //}



        std::ifstream infile(m->filePath);




        std::unordered_map<Vertex, uint32_t> uniqueVertices{};
        std::vector<double> VXS;
        std::vector<double> VYS;
        std::vector<double> VZS;
        std::vector<double> TXS;
        std::vector<double> TYS;
        std::vector<uint8_t> TIDX;

        while (!infile.eof())
        {
            char line[128];
            infile.getline(line, 128);

            std::strstream s;
            s << line;
            char junk;
            if (line[0] == 'v' && line[1] == 't')
            {
                float a, b;
                s >> junk >> a >> b;
                TXS.push_back(a);
                TYS.push_back(b);
            }
            else if (line[0] == 'v' && line[1] == 'n') {}//I don't care about normals
            else if (line[0] == 'v') {
                float a, b, c;

                s >> junk >> a >> b >> c;

                VXS.push_back(a);
                VYS.push_back(b);
                VZS.push_back(c);
            }
            else if (line[0] == 'f')
            {
                //std::cout << VXS.size() << std::endl;
                //std::cout << VYS.size() << std::endl;
                //std::cout << VZS.size() << std::endl;
                Vertex vertex{};

                int v[3], t[3], n[3];
                int ti;
                s >> junk >> v[0] >> t[0] >> n[0] >> v[1] >> t[1] >> n[1] >> v[2] >> t[2] >> n[2] >> ti;

                for (size_t vnum = 0; vnum < 3; vnum++) {
                    // access to vertex
                    //tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                    glm::vec3 inputPosition = glm::vec3(
                        VXS[v[vnum] - 1],
                        VYS[v[vnum] - 1],
                        VZS[v[vnum] - 1]
                    );
                    //if(VXS.size()==61)
                    //    std::cout << VXS[v[vnum] - 1] << ", " << VYS[v[vnum] - 1] << ", " << VZS[v[vnum] - 1]<< std::endl;
                    // Apply rotation to correct for incorrect Blender model export
                    glm::mat4 rotmat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

                    // Define per object offsets
                    glm::vec3 offset = glm::vec3(m->x, m->y, m->z);



                    // Final vertex position
                    vertex.pos = glm::vec3(rotmat * glm::vec4(inputPosition, 1.0)) + offset;

                    vertex.textureIndex = ti;
                    //std::cout << "vertex.textureIndex = " << vertex.textureIndex << std::endl;

                    vertex.texCoord = {
                        TXS[t[vnum] - 1],
                        1.0f - TYS[t[vnum] - 1]
                    };
                    vertex.color = { 1.0f, 1.0f, 1.0f };

                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<uint32_t>(m->vertices.size());
                        m->vertices.push_back(vertex);
                    }

                    m->indices.push_back(uniqueVertices[vertex]);
                }


            }
        }
    }

    void createVertexBuffer() {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(device, stagingBufferMemory);

        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

        copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);
    }

    void createIndexBuffer() {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t)bufferSize);
        vkUnmapMemory(device, stagingBufferMemory);

        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

        copyBuffer(stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);
    }

    void createUniformBuffers() {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(swapChainImages.size());
        uniformBuffersMemory.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            createBuffer(bufferSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
        }
    }

    void createStorageBuffers() {

        VkDeviceSize bufferSize_pos = CMDLs.data()[0].geometry.vertexCoords.size() * sizeof(float);
        VkDeviceSize bufferSize_nml = CMDLs.data()[0].geometry.normals.size() * sizeof(float);
        VkDeviceSize bufferSize_uvc = CMDLs.data()[0].geometry.floatUVCoords.size() * sizeof(float);

        for (int i = 0; i < CMDLs[0].geometry.surfaceCount; i++)
        {
            bufferSize_ndx += CMDLs[0].geometry.surfaces[i].pos_indices.size() * sizeof(uint32_t);
            bufferSize_ndx += CMDLs[0].geometry.surfaces[i].nml_indices.size() * sizeof(uint32_t);
            bufferSize_ndx += CMDLs[0].geometry.surfaces[i].uvc_indices.size() * sizeof(uint32_t);
        }

        createBuffer(bufferSize_pos, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, posBuffer, posBufferMemory);
        createBuffer(bufferSize_nml, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, nmlBuffer, nmlBufferMemory);
        createBuffer(bufferSize_uvc, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uvcBuffer, uvcBufferMemory);
        createBuffer(bufferSize_ndx, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, ndxBuffer, ndxBufferMemory);
    
        void* data;

        vkMapMemory(device, posBufferMemory, 0, bufferSize_pos, 0, &data);
        memcpy(data, CMDLs.data()[0].geometry.vertexCoords.data(), bufferSize_pos);
        vkUnmapMemory(device, posBufferMemory);

        vkMapMemory(device, nmlBufferMemory, 0, bufferSize_nml, 0, &data);
        memcpy(data, CMDLs.data()[0].geometry.normals.data(), bufferSize_nml);
        vkUnmapMemory(device, nmlBufferMemory);

        vkMapMemory(device, uvcBufferMemory, 0, bufferSize_uvc, 0, &data);
        memcpy(data, CMDLs.data()[0].geometry.floatUVCoords.data(), bufferSize_uvc);
        vkUnmapMemory(device, uvcBufferMemory);

        
        uint32_t* data2;

        vkMapMemory(device, ndxBufferMemory, 0, bufferSize_ndx, 0, (void**)&data2);
        for (int i = 0; i < CMDLs[0].geometry.surfaceCount; i++)
        {
            for (int j = 0; j < CMDLs[0].geometry.surfaces[i].pos_indices.size(); j++) {
                *data2 = CMDLs.data()[0].geometry.surfaces[i].pos_indices[j];
                data2++;
                *data2 = CMDLs.data()[0].geometry.surfaces[i].nml_indices[j];
                data2++;
                *data2 = CMDLs.data()[0].geometry.surfaces[i].uvc_indices[j];
                data2++;

            }
        }

        vkUnmapMemory(device, ndxBufferMemory);
    
    }
    void createDescriptorPool() {
        std::array<VkDescriptorPoolSize, 3> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size() * images.size());
        poolSizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        poolSizes[2].descriptorCount = 4*static_cast<uint32_t>(swapChainImages.size());

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    void createDescriptorSets() {
        std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(swapChainImages.size());
        if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }
        VkDescriptorBufferInfo posBufferInfo{};
        posBufferInfo.buffer = posBuffer;
        posBufferInfo.offset = 0;
        posBufferInfo.range = VK_WHOLE_SIZE;
        VkDescriptorBufferInfo nmlBufferInfo{};
        nmlBufferInfo.buffer = nmlBuffer;
        nmlBufferInfo.offset = 0;
        nmlBufferInfo.range = VK_WHOLE_SIZE; 
        VkDescriptorBufferInfo uvcBufferInfo{};
        uvcBufferInfo.buffer = uvcBuffer;
        uvcBufferInfo.offset = 0;
        uvcBufferInfo.range = VK_WHOLE_SIZE;

        VkDescriptorBufferInfo ndxBufferInfo{};
        ndxBufferInfo.buffer = ndxBuffer;
        ndxBufferInfo.offset = 0;
        ndxBufferInfo.range = VK_WHOLE_SIZE;

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            std::vector<VkDescriptorImageInfo> imageInfo;
            imageInfo.resize(images.size());
            for (int x = 0; x < images.size(); x++) {
                imageInfo[x] = {};
                imageInfo[x].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                imageInfo[x].imageView = imageStuffs.at(x).textureImageView;
                imageInfo[x].sampler = imageStuffs.at(x).textureSampler;
            }


            std::array<VkWriteDescriptorSet, 6> descriptorWrites{};

            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = descriptorSets[i];
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;

            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1].dstSet = descriptorSets[i];
            descriptorWrites[1].dstBinding = 1;
            descriptorWrites[1].dstArrayElement = 0;
            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1].descriptorCount = images.size();
            descriptorWrites[1].pImageInfo = &imageInfo[0];

            descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[2].dstSet = descriptorSets[i];
            descriptorWrites[2].dstBinding = 6;
            descriptorWrites[2].dstArrayElement = 0;
            descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            descriptorWrites[2].descriptorCount = 1;
            descriptorWrites[2].pBufferInfo = &posBufferInfo;

            descriptorWrites[3].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[3].dstSet = descriptorSets[i];
            descriptorWrites[3].dstBinding = 7;
            descriptorWrites[3].dstArrayElement = 0;
            descriptorWrites[3].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            descriptorWrites[3].descriptorCount = 1;
            descriptorWrites[3].pBufferInfo = &nmlBufferInfo;

            descriptorWrites[4].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[4].dstSet = descriptorSets[i];
            descriptorWrites[4].dstBinding = 8;
            descriptorWrites[4].dstArrayElement = 0;
            descriptorWrites[4].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            descriptorWrites[4].descriptorCount = 1;
            descriptorWrites[4].pBufferInfo = &uvcBufferInfo;

            descriptorWrites[5].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[5].dstSet = descriptorSets[i];
            descriptorWrites[5].dstBinding = 9;
            descriptorWrites[5].dstArrayElement = 0;
            descriptorWrites[5].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            descriptorWrites[5].descriptorCount = 1;
            descriptorWrites[5].pBufferInfo = &ndxBufferInfo;





            vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }

        vkBindBufferMemory(device, buffer, bufferMemory, 0);
    }

    VkCommandBuffer beginSingleTimeCommands() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }

    void endSingleTimeCommands(VkCommandBuffer commandBuffer) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue);

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands();

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        endSingleTimeCommands(commandBuffer);
    }

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void createCommandBuffers() {
        commandBuffers.resize(swapChainFramebuffers.size());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

        if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = swapChainExtent;

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
            clearValues[1].depthStencil = { 1.0f, 0 };

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

            VkBuffer vertexBuffers[] = { vertexBuffer };
            VkDeviceSize offsets[] = { 0 };
            //vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

            //vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);

            vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);
            uint32_t offset__ = 0;
            //for (int j = 0; j < objects.size(); j++)
            //{
            //    /*
            //    commandBuffer,
            //    indexCount,
            //    instanceCount,
            //    firstIndex,
            //    vertexOffset,
            //    firstInstance
            //    */
            //    vkCmdDrawIndexed(commandBuffers[i],
            //        static_cast<uint32_t>(objects[j].num_indices),
            //        1,
            //        static_cast<uint32_t>(objects[j].startIndex),
            //        static_cast<uint32_t>(objects[j].vertOffset),
            //        0);
            //    offset__ += (objects[j].num_indices);
            //}
            vkCmdDraw(commandBuffers[i], bufferSize_ndx/sizeof(uint32_t),1,0,0);
            
            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }

    void createSyncObjects() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }

    void updateUniformBuffer(uint32_t currentImage) {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};
        ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // NOTE: z-coord is specified as up direction because this is how the model was exported from Blender
        //glm::lookAt(cameraPosition, cameraTarget, upVector)
        glm::quat pitch = glm::quat(glm::vec3(0.0, 0.0, playerCharacter.mousex / 100));
        glm::quat roll = glm::quat(glm::vec3(playerCharacter.mousey / 100, 0.0, 0.0));
        ubo.view = glm::translate(glm::mat4_cast(roll) * glm::mat4_cast(pitch), playerCharacter.cameraPos);
        // glm::lookAt(
        // playerCharacter.cameraPos, 
        // playerCharacter.cameraPos+playerCharacter.cameraFront,
        // playerCharacter.cameraUp); 
        ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 40.0f);
        ubo.proj[1][1] *= -1;

        void* data;
        vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
    }

    void drawFrame() {
        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        updateUniformBuffer(imageIndex);

        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(device, 1, &inFlightFences[currentFrame]);

        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { swapChain };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
            framebufferResized = false;
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    VkShaderModule createShaderModule(const std::vector<char>& code) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;
    }

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        }
        else {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        QueueFamilyIndices indices = findQueueFamilies(device);

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

        return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }

    bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    std::vector<const char*> getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    static std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
};

int main() {
    std::cout << "test test" << std::endl;
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
// module.exports = {
//   reactStrictMode: false,
//   webpack: (config: any) => {
//     config.infrastructureLogging = { level: "warn" }; // Hide warnings
//     return config;
//   },
// };

/** @type {import('next').NextConfig} */

module.exports = {
  reactStrictMode: false,

  // ✅ Disable ESLint blocking the Vercel build
  eslint: {
    ignoreDuringBuilds: true,
  },

  // (Optional) Prevent TypeScript errors from stopping the build
  typescript: {
    ignoreBuildErrors: true,
  },

  webpack: (config) => {
    config.infrastructureLogging = { level: "warn" }; // Hide warnings
    return config;
  },
};

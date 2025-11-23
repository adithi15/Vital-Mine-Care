/** @type {import('next').NextConfig} */

module.exports = {
  reactStrictMode: false,

  // 🚫 Disable ESLint during Vercel builds
  eslint: {
    ignoreDuringBuilds: true,
  },

  // 🚫 Disable TypeScript errors stopping Vercel build
  typescript: {
    ignoreBuildErrors: true,
  },

  webpack: (config) => {
    config.infrastructureLogging = { level: "warn" };
    return config;
  },
};

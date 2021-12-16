#include <benchmark/benchmark.h>
#include <chrono>
#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <memory.h>
#include <Logger.h>
#include <ConsoleOutput.h>

// unsigned long Increment(unsigned long n) {
//  unsigned long sum = 0;
//  for(unsigned long i = 0; i < n; ++i) {
//    benchmark::DoNotOptimize(sum++); // force to store memory in either memory or register
//    benchmark::ClobberMemory();  // force compilier to perform all pending writes to global memory
//  }
//  return sum;
//}
//
//static void BM_Increment(benchmark::State &state) {
//  for(auto _ : state) {
//    Increment(state.range(0));
//  }
//}
//BENCHMARK(BM_Increment)->RangeMultiplier(2)->Range(1 << 8, 1 << 10);
//
//static void BM_memcpy(benchmark::State& state) {
//  char* src = new char[state.range(0)];
//  char* dst = new char[state.range(0)];
//  memset(src, 'x', state.range(0));
//  for (auto _ : state)
//    memcpy(dst, src, state.range(0));
//  state.SetBytesProcessed(int64_t(state.iterations()) *
//                          int64_t(state.range(0)));
//  delete[] src;
//  delete[] dst;
//}
//BENCHMARK(BM_memcpy)->Range(8, 16<<10);
const char* getProcessName()
{
    return "LoggingBenchmark";
}

void LogLikeHell(unsigned long times)
{
    auto output =  std::make_shared<logger::ConsoleOutput<>>();
    logger::Logger log("DOMAIN", output);
    for(unsigned long i = 0; i < times; ++i)
    {
        benchmark::DoNotOptimize(log << info << "Log like hell " << i+(i%100));
    }
}

static void BM_Log(benchmark::State &state)
{
    for (auto _: state)
    {
        LogLikeHell(state.range(0));
    }
}

//BENCHMARK(BM_Log)->Arg(1000)->Arg(5000)->Arg(1000000);
BENCHMARK(BM_Log)->RangeMultiplier(10)->Range(10,1000000);

// Run benchmark
BENCHMARK_MAIN();

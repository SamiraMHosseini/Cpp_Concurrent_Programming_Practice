#include <iostream>
int  func(int counter)
{
	static const int N = 5;
	std::vector<std::future<int>> futures;

	if (counter > N)
	{
		return counter;
	}
	std::future<int> fut = std::async(std::launch::async, &func, counter + 1); //Spawning a new thread
	futures.push_back(std::move(fut));
	std::for_each(futures.begin(), futures.end(), [&](auto& item)

		{
			int result = item.get(); //Waiting for the result to become available
			std::cout << "result: " << result << '\n';
		});

	return counter;

}


int main()
{
	int counter = 1;
	std::future<int> fut = std::async(std::launch::async, &func, counter);
	fut.wait();
	int result = fut.get();
	std::cout << "result: " << result << '\n';
	return 0;
}


-- function set_net(file_net)
-- 	path_to_net = file_net
-- end

function main(img)
	require 'torch'
	require 'nn'

	require 'cutorch'
	require 'cunn'

	net = torch.load('/home/dmitry/Projects/DNN-develop/torch/results/CNN.net')
	-- net = torch.load('/home/dmitry/tmp/net.net')

	img = torch.DoubleTensor(img)

	mean = img:mean()
	std = img:std()

	img:add(-mean)
	img:div(std)

	output = net:forward(img:cuda():view(1, 28, 28))

	min = output:min()
	for i=1,10 do
		if output[i] == min then
			j = i
			break
		end
	end

	print(output)

	if j == 10 then j = 0 end
	return j, -min
end

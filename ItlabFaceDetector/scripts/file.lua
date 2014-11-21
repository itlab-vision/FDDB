require 'torch'
require 'nn'

function loadNetModel(path)
	net = torch.load(path)
end

function predict(img)
	img = torch.DoubleTensor(img)

	mean = img:mean()
	std = img:std()

	img:add(-mean)
	img:div(std)

	output = net:forward(img:view(1, 28, 28))

	max = output:max()
	for i=1,10 do
		if output[i] == max then
			j = i
			break
		end
	end

	--print(output)

	if j == 10 then j = 0 end
	return j, -max
end
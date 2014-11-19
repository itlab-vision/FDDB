-- function set_net(file_net)
-- 	path_to_net = file_net
-- end

require 'torch'
require 'nn'

--require 'cutorch'
--require 'cunn'

function main(img)

	net = torch.load('/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/net/linear-MNIST.net')
	-- net = torch.load('/home/dmitry/tmp/net.net')

	--print (img[14])

	img = torch.DoubleTensor(img)

	mean = img:mean()
	std = img:std()

	img:add(-mean)
	img:div(std)

	output = net:forward(img)

	min = output:min()
	for i=1,10 do
		if output[i] == min then
			j = i
			break
		end
	end

	--print(output)

	if j == 10 then j = 0 end
	return j, -min
end

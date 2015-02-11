function load_modules()
    require 'torch'
    require 'nn'
    require 'image'
end

function loadNetModel(path)
	net = torch.load(path)
	net = net:float()

	neighborhood = image.gaussian1D(5)
   	normalization = nn.SpatialContrastiveNormalization(1, neighborhood, 1):float()
end

function preprocessing(img)
	img = img:float()
	img = image.rgb2yuv(img)

   	local mean = {-0.000030917338317801, 0.00044114560185953, -0.00055240759852816}
   	local std = {0.31813675177978, 0.10214817756977, 0.097131512356802}
   	for i,channel in ipairs(channels) do
        img[{ i,{},{} }]:add(-mean[i])
    	img[{ i,{},{} }]:div(std[i])
   	end

   	for c in ipairs(channels) do
        img[{ {c},{},{} }] = normalization:forward(img[{ {c},{},{} }])
   	end

	return img
end

function predict(img)
	img = torch.reshape(img, 3, 32, 32)

	img = preprocessing(img)
	
	output = net:forward(img)

	max = output:max()
	for i=1,2 do
		if output[i] == max then
			j = i
			break
		end
	end

	return j, -max
end
